/*	Class that creates a quadtree

	@author Hector Martinez Cebrian
	@version 2013-05-08
	@MODIFIED	2016-06-06
	@MODIFIER Ramón Mollá
	@MODIFIED: Removed NE, NW, SE, SW attributes and replaced by an array of Quadtrees calle QTSons. QT_ORIENTATION type enumeration introduced
*/

#include <math.h>
#include <QuadtreeRoot.h>
#include <UGKCharacter.h>

using namespace UGK;

Quadtree::Quadtree(float _x, float _y, float _width, float _height, int _level, int _maxLevel)
{
	unsigned int i;		

	x=_x;
	y=_y;
	width=_width;
	height=_height;
	level=_level;
	maxLevel=_maxLevel;
	minX=500000;
	minY=500000;
	maxX=-1000000;
	maxY=-1000000;
	cantidad=0;

	if(level!=maxLevel)
	{
		QTSons[QT_NE] = new Quadtree(x+width/2.f,y,width/2.f,height/2.f,level+1,maxLevel);
		QTSons[QT_NW] = new Quadtree(x,y,width/2.f,height/2.f,level+1,maxLevel);
		QTSons[QT_SE] = new Quadtree(x+width/2.f,y+height/2.f,width/2.f,height/2.f,level+1,maxLevel);
		QTSons[QT_SW] = new Quadtree(x,y+height/2.f,width/2.f,height/2.f,level+1,maxLevel);
	}
	else 
		for (i = 0; i < QT_MAX_ORIENTATION;i++)
			QTSons[i] = NULL;
}
	
Quadtree::~Quadtree()
{
	unsigned int i;		

	if(level!=maxLevel)
		for (i = 0; i < QT_MAX_ORIENTATION;i++)
			if (NULL != QTSons[i]) delete QTSons[i];
}

CharacterList Quadtree::GetNearestObjectsTo(float _x, float _y, float radius)
{
	unsigned int i;		

	if(level==maxLevel){
		return characters;
	}

	CharacterList returnCharacters,
						childReturnCharacters;
	
	for (i = 0; i < QT_MAX_ORIENTATION;i++)
		if (Contains(QTSons[i],_x,_y,radius))
		{
			childReturnCharacters=QTSons[i]->GetNearestObjectsTo(_x,_y,radius);
			returnCharacters.insert(returnCharacters.end(),childReturnCharacters.begin(),childReturnCharacters.end());
		}

	return returnCharacters;
}

void Quadtree::AddCharacter(CCharacter *character)
{
	unsigned int i;

	cantidad++;

	if(level==maxLevel){
		characters.push_back(character);
#ifdef CHAR_USE_QUADTREE
		character->IncQTAmount();
#elif defined CHAR_USE_AABB
#elif defined CHAR_USE_OBB
#endif
		return;
	}
		
	for (i = 0; i < QT_MAX_ORIENTATION;i++)
		if (Contains(QTSons[i], character))
		{
			QTSons[i]->AddCharacter(character);
			return;
		}
}

bool Quadtree::RemoveCharacter(CCharacter *character)
{
	unsigned int i, j;
	bool Result;

	if(level==maxLevel){
		unsigned int i=0;
		for(vector<CCharacter *>::iterator it=characters.begin();it!=characters.end();){
				
			if(*it==character){
				it=characters.erase(it);
#ifdef CHAR_USE_QUADTREE
				character->DecQTAmount();
#elif defined CHAR_USE_AABB
#elif defined CHAR_USE_OBB
#endif
				cantidad--;
				return true;
			}else{it++;}
		}
		return false;
	}
	
	for (i = 0; i < QT_MAX_ORIENTATION;i++)
			if(Contains(QTSons[i],character))
				if (!QTSons[i]->RemoveCharacter(character))
				{
					Result = false;
					for (j = 0; j < QT_MAX_ORIENTATION; j++)
					if (i != j)
						Result = Result || QTSons[j]->RemoveCharacter(character);
					return Result;
				}
	return false;
}

void Quadtree::Purge()
{
	unsigned int i;

	if(level==maxLevel){
			
		unsigned int i=0;
		while(i<characters.size())			
			if(characters.at(i)->Type>=0 && characters.at(i)->Type<20 /*Y Contains(this,characters.at(i))*/)
				i++;
			else
				characters.erase(characters.begin()+i);
	}
	else
		for (i = 0; i < QT_MAX_ORIENTATION;i++)
			QTSons[i]->Purge();	
}

bool Quadtree::UpdateCharacter(CCharacter *character)
{
	bool ret;
	unsigned int i, j;
	
	if(level==maxLevel){
		//In this node exist the character
		if(Contains(this,character)) return true;
		else{
			unsigned int i=0;
			for(;i<characters.size();i++)
				if(characters.at(i)==character){
					characters.erase(characters.begin()+i);
#ifdef CHAR_USE_QUADTREE
					character->DecQTAmount();
#elif defined CHAR_USE_AABB 
#elif defined CHAR_USE_OBB 
#endif
					cantidad--;
					break;
				}
			}
		return false;
	}

	for (i = 0; i < QT_MAX_ORIENTATION;i++)
		if(BeforeContains(QTSons[i],character))
		{
			ret=QTSons[i]->UpdateCharacter(character);
			if(!ret)
			{
				for (j = 0; j < QT_MAX_ORIENTATION;j++)
					if (i!=j)
						if(Contains(QTSons[j],character)){
							QTSons[j]->AddCharacter(character);
							return true;
						}
				return false;
			}else return true;
		}
	AddCharacter(character);
	return false;	
}

void Quadtree::Clear()
{
	unsigned int i;

	if(level==maxLevel){
		characters.clear();
		return;
	}
	
	for (i = 0; i < QT_MAX_ORIENTATION;i++)
		QTSons[i]->Clear();
}

bool Quadtree::Contains(Quadtree *child, CCharacter *character){
	
	return/* !(character->Position.v[XDIM] < child->x ||
		character->Position.v[YDIM] < child->y ||
		character->Position.v[XDIM] > child->x + child->width  ||
		character->Position.v[YDIM] > child->y + child->height);*/
		(character->Position.v[XDIM]>= child->x && character->Position.v[XDIM]<child->x+child->width) &&
		(character->Position.v[YDIM]>= child->y && character->Position.v[YDIM]<child->y+child->height);
}

bool Quadtree::BeforeContains(Quadtree *child, CCharacter *character){
	
	return /*!(character->PositionPrev.v[XDIM] < child->x ||
		character->PositionPrev.v[YDIM] < child->y ||
		character->PositionPrev.v[XDIM] > child->x + child->width  ||
		character->PositionPrev.v[YDIM] > child->y + child->height);*/
	
		(character->PositionPrev.v[XDIM]>= child->x && character->PositionPrev.v[XDIM]<child->x+child->width) &&
		(character->PositionPrev.v[YDIM]>= child->y && character->PositionPrev.v[YDIM]<child->y+child->height);
}

bool Quadtree::Contains(Quadtree *child, float _x, float _y, float radius){
	
	
	float circleDistanceX = abs(_x - child->x - child->width/2);
	float circleDistanceY = abs(_y - child->y - child->height/2);
 
	if (circleDistanceX > (child->width/2 + radius)) { return false; }
	if (circleDistanceY > (child->height/2 + radius)) { return false; }
 
	if (circleDistanceX <= (child->width/2)) { return true; }
	if (circleDistanceY <= (child->height/2)) { return true; }
 
	float cornerDistance_sq = pow(circleDistanceX - child->width/2, 2) + pow(circleDistanceY - child->height/2, 2);
 
	return (cornerDistance_sq <= (pow(radius, 2)));	
}

bool Quadtree::ContainsBigCharacter(Quadtree *child, CCharacter *character){
		
	return (child->x + child->width		> character->Position.v[XDIM]-(character->AABB[CHAR_BBSIZE][XDIM].Value /2.f) &&
			child->x					< character->Position.v[XDIM]+(character->AABB[CHAR_BBSIZE][XDIM].Value /2.f) &&
			child->y + child->height	> character->Position.v[YDIM]-(character->AABB[CHAR_BBSIZE][YDIM].Value /2.f) &&
			child->y					< character->Position.v[YDIM]+(character->AABB[CHAR_BBSIZE][YDIM].Value /2.f)
			);


}

void Quadtree::AddBigCharacter(CCharacter *character)
{
	unsigned int i;

	cantidad++;

	if(level==maxLevel){
		characters.push_back(character);
#ifdef CHAR_USE_QUADTREE
		character->IncQTAmount();
#endif
		return;
	}
		
	for (i = 0; i < QT_MAX_ORIENTATION;i++)
		if(ContainsBigCharacter(QTSons[i],character))
			QTSons[i]->AddBigCharacter(character);
}

void Quadtree::RemoveBigCharacter(CCharacter *character){}	

void Quadtree::Render()
{
	unsigned int i;

	if(level==maxLevel){
		if(characters.size()==0) glColor3f(1.0,0.0,0.0);
		else {glColor3f(0.0,(GLfloat)1.0/characters.size(),0.0);
			
		glBegin(GL_LINE_STRIP);
		glVertex3f(x,y,0);
		glVertex3f(x,y+width,0);
		glVertex3f(x+height,y+width,0);
		glVertex3f(x+height,y,0);
		glVertex3f(x,y,0);
		glEnd();}
	}
	if(level!=maxLevel)
	{
		/*glColor3f(0.0f,0.0f,1.0f);
		glBegin(GL_LINE_STRIP);
		glVertex3f(x,y,0);
		glVertex3f(x,y+width,0);
		glVertex3f(x+height,y+width,0);
		glVertex3f(x+height,y,0);
		glVertex3f(x,y,0);
		glEnd();
	*/
	for (i = 0; i < QT_MAX_ORIENTATION;i++)
		QTSons[i]->Render();
	}
}