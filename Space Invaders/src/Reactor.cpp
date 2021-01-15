/**
*	@file Reactor.cpp
// Reactor class
//
// These values are by default. They have to be overwritten in the initialization phase
// when reading the default values from the "initialization.html" file

	@author Ramon Molla
	@version 2011-09-11
*/

#include <Player.h>
#include <UGKMeshManager.h>

#include <SITexturesResources.h>
#include <GameCharacters.h>

extern CMeshesManager	MeshesManager;

CReactor::CReactor()
{
	alpha		= 0.83f;
	alpha_down	= true;

	ln			= 0.00;	// particules externes des lasers + grandes pour le mode 3D_LINES
	ln2			= 0.00;	// particules internes des réacteurs + petites pour le mode *non* 3D_LINES

	PhysicMode	= 	UGKPHY_LIGHT;	//Visible and untouchable. No AABB management

	AABB[CHAR_BBSIZE][XDIM].Value = 0.3;
	AABB[CHAR_BBSIZE][YDIM].Value = 0.3;
	AABB[CHAR_BBSIZE][ZDIM].Value = 0.0;
	UpdateAABB();

	SetLocalTimers(CR_MAX_TIMERS);

	Type		= CHARS_REACTOR;
}

void CReactor::RenderLaser(unsigned int L)
{
	float UGKALG_ModelView[16];
	CTexturesManager * TextMngr = (CTexturesManager *)Directory[CHARS_TEXTURES_MNGR_REF];
	unsigned int i, k, l;

	TextMngr->Textures[CTM_PARTICLE]->SetTexture();

	glColor4f(0.120f, 0.340f, 0.953f, alpha);					// bleu
	glPushMatrix();

	glTranslatef(Players[CurrentPlayer]->Laser[L].Position.v[XDIM],
		Players[CurrentPlayer]->Laser[L].Position.v[YDIM],
		Players[CurrentPlayer]->Laser[L].Position.v[ZDIM]);

	glRotatef(Players[CurrentPlayer]->Laser[L].Mesh->modelo.rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(Players[CurrentPlayer]->Laser[L].Mesh->modelo.rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(Players[CurrentPlayer]->Laser[L].Mesh->modelo.rot.z, 0.0f, 0.0f, 1.0f);

	glTranslatef(0.0, 0.03, 0.12);

	// get the current modelview matrix
	glGetFloatv(GL_MODELVIEW_MATRIX, UGKALG_ModelView);

	// undo all rotations (beware all scaling is lost as well)
	for (k = 0; k<3; k++)
	for (l = 0; l<3; l++) {
		if (k == l)
			UGKALG_ModelView[k * 4 + l] = 1.0;
		else
			UGKALG_ModelView[k * 4 + l] = 0.0;
	}

	// set the modelview with no rotations and scaling
	glLoadMatrixf(UGKALG_ModelView);

	for (i = 0; i <= 2; i++)
	{
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);	glVertex2f(-.30, +.30);
		glTexCoord2f(0, 0);	glVertex2f(-.30, -.30);
		glTexCoord2f(1, 0);	glVertex2f(+.30, -.30);
		glTexCoord2f(1, 1);	glVertex2f(+.30, +.30);
		glEnd();
	}

	TextMngr->Textures[CTM_PARTICLE4]->SetTexture();

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);	glVertex2f(-.60 - ln, +.60 + ln);
	glTexCoord2f(0, 0);	glVertex2f(-.60 - ln, -.60 - ln);
	glTexCoord2f(1, 0);	glVertex2f(+.60 + ln, -.60 - ln);
	glTexCoord2f(1, 1);	glVertex2f(+.60 + ln, +.60 + ln);
	glEnd();

	glPopMatrix();
}

void CReactor::Render ()
{
	float UGKALG_ModelView [16];
	unsigned int i,k,l;
	CTexturesManager * TextMngr = (CTexturesManager *) Directory[CHARS_TEXTURES_MNGR_REF];
	HRT_Timems RenderPeriod = Timer[CR_RND_PERIOD].GetAlarmPeriodms();

	// Pas de lumière sur les réacteurs
	glDisable	(SIGLB_PLAYER_LIGHT);
	glDisable	(GL_LIGHTING);

	// REACTEURS DU PLAYER
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glFrontFace(GL_CCW);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);

	TextMngr->Textures[CTM_PARTICLE]->SetTexture();
	
	// Reactors alpha
	if (alpha > 0.83 && alpha_down)
		alpha -= 0.005*RenderPeriod;
	else if (alpha < 1.1 && !alpha_down)
		alpha += 0.005*RenderPeriod;
	else if (alpha < 0.83 && alpha_down)
		alpha_down = false;
	else if (alpha > 0.83 && !alpha_down)
		alpha_down = true;

	glColor4f (0.953f, 0.340f, 0.120f, alpha);					// red

	if (CHAR_LINES3D == RenderMode)
		 ln  = 0.20;
	else ln2 = 0.02;

	// Player Reactors
	glPushMatrix();

		// On player position...
		glTranslatef(Position.v[XDIM], Position.v[YDIM], Position.v[ZDIM]);
		
		glRotatef(Players[CurrentPlayer]->Mesh->modelo.rot.x, 1.0f, 0.0f, 0.0f);
		glRotatef(Players[CurrentPlayer]->Mesh->modelo.rot.y, 0.0f, 1.0f, 0.0f);
		glRotatef(Players[CurrentPlayer]->Mesh->modelo.rot.z, 0.0f, 0.0f, 1.0f);

		// Left Reactor (billboarding)
		glPushMatrix();
			
			if (CHAR_LINES3D == RenderMode)
				 glTranslatef(- 0.23, 0.03, 0.33);
			else glTranslatef(- 0.23, 0.03, 0.35);

			// get the current UGKALG_ModelView matrix
			glGetFloatv(GL_MODELVIEW_MATRIX , UGKALG_ModelView);

			// undo all rotations (beware all scaling is lost as well)
				for( k=0; k<3; k++ ) 
					for( l=0; l<3; l++ ) {
						if ( k==l )
							UGKALG_ModelView[k*4+l] = 1.0;
						else
							UGKALG_ModelView[k*4+l] = 0.0;
					}

			// set the UGKALG_ModelView with no rotations and scaling
			glLoadMatrixf(UGKALG_ModelView);

			for (i=0; i<=2; i++)
				{
					glBegin (GL_QUADS);
						glTexCoord2f (0,1);	glVertex2f ( - .30+ln2, +.30-ln2);
						glTexCoord2f (0,0);	glVertex2f ( - .30+ln2, -.30+ln2);
						glTexCoord2f (1,0);	glVertex2f ( + .30-ln2, -.30+ln2);
						glTexCoord2f (1,1);	glVertex2f ( + .30-ln2, +.30-ln2);
					glEnd ();
				}
		
			TextMngr->Textures[CTM_PARTICLE4]->SetTexture();

			glBegin (GL_QUADS);
				glTexCoord2f (0,1);	glVertex2f ( - .70, +.70);
				glTexCoord2f (0,0);	glVertex2f ( - .70, -.70);
				glTexCoord2f (1,0);	glVertex2f ( + .70, -.70);
				glTexCoord2f (1,1);	glVertex2f ( + .70, +.70);
			glEnd ();

		glPopMatrix();

		// Right Reactor (billboarding)
		glPushMatrix();

			TextMngr->Textures[CTM_PARTICLE]->SetTexture();
			
			if (CHAR_LINES3D == RenderMode)
					 glTranslatef(+ 0.23, 0.03, 0.33);
				else glTranslatef(+ 0.23, 0.03, 0.35);

			// get the current UGKALG_ModelView matrix
			glGetFloatv(GL_MODELVIEW_MATRIX , UGKALG_ModelView);

			// undo all rotations (beware all scaling is lost as well). Only translation is maintained
				for( k=0; k<3; k++ ) 
					for( l=0; l<3; l++ ) {
						if ( k==l )
							UGKALG_ModelView[k*4+l] = 1.0;
						else
							UGKALG_ModelView[k*4+l] = 0.0;
					}
		
			// set the UGKALG_ModelView with no rotations and scaling
			glLoadMatrixf(UGKALG_ModelView);

			for (i=0; i<=2; i++)
				{
					glBegin (GL_QUADS);
						glTexCoord2f (0,1);	glVertex2f ( - .30+ln2, +.30-ln2);
						glTexCoord2f (0,0);	glVertex2f ( - .30+ln2, -.30+ln2);
						glTexCoord2f (1,0);	glVertex2f ( + .30-ln2, -.30+ln2);
						glTexCoord2f (1,1);	glVertex2f ( + .30-ln2, +.30-ln2);
					glEnd ();
				}

			TextMngr->Textures[CTM_PARTICLE4]->SetTexture();

			glBegin (GL_QUADS);
				glTexCoord2f (0,1);	glVertex2f ( - .70, +.70);
				glTexCoord2f (0,0);	glVertex2f ( - .70, -.70);
				glTexCoord2f (1,0);	glVertex2f ( + .70, -.70);
				glTexCoord2f (1,1);	glVertex2f ( + .70, +.70);
			glEnd ();

		glPopMatrix();
	glPopMatrix();

	// Enabling everything again, as the beginning
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glDisable(GL_BLEND);

	glEnable	(SIGLB_PLAYER_LIGHT);
	glEnable	(GL_LIGHTING);
}
