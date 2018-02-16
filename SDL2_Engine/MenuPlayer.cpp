#include "MenuPlayer.h"
#include "Text.h"
#include "Color.h"
#include "Input.h"
#include "Scene.h"
#include "Engine.h"
#include "MainScene.h"

MenuPlayer::MenuPlayer()
{
}

Rect * MenuPlayer::GetRect()
{
	return nullptr;
}

void MenuPlayer::SetRect(Rect * _pRect)
{
}

void MenuPlayer::Update(float _deltaTime)
{
	// decrease time
	m_time -= _deltaTime;

	// if time under 0 change bright
	if (m_time <= 0)
	{
		m_time = 0.1f;
		m_bright = !m_bright;

		// if start chosen
		if (m_start)
		{
			// set end text color to white
			m_pEndText->GetColor()->r = 255;
			m_pEndText->GetColor()->g = 255;
			m_pEndText->GetColor()->b = 255;

			// if bright
			if (m_bright)
			{
				m_pStartText->GetColor()->r = 255;
				m_pStartText->GetColor()->g = 255;
				m_pStartText->GetColor()->b = 255;
			}
			else
			{
				m_pStartText->GetColor()->r = 128;
				m_pStartText->GetColor()->g = 128;
				m_pStartText->GetColor()->b = 128;
			}
		}

		// if end chosen
		else
		{
			// set start text color to white
			m_pStartText->GetColor()->r = 255;
			m_pStartText->GetColor()->g = 255;
			m_pStartText->GetColor()->b = 255;

			// if bright
			if (m_bright)
			{
				m_pEndText->GetColor()->r = 255;
				m_pEndText->GetColor()->g = 255;
				m_pEndText->GetColor()->b = 255;
			}
			else
			{
				m_pEndText->GetColor()->r = 128;
				m_pEndText->GetColor()->g = 128;
				m_pEndText->GetColor()->b = 128;
			}
		}
	}

	// change selection
	if (Input::GetKeyDown(SDL_SCANCODE_W) ||
		Input::GetKeyDown(SDL_SCANCODE_S))
	{
		m_start = !m_start;
	}

	// if enter is pressed
	if (Input::GetKeyDown(SDL_SCANCODE_RETURN))
	{
		// if start chosen
		if (m_start)
		{
			// create new mainscene and change scene
			MainScene* mainScene = new MainScene(m_pScene->GetEngine());
			m_pScene->GetEngine()->ChangeScene(mainScene);
		}

		// if end chosen
		else
		{
			// quit engine
			m_pScene->GetEngine()->Quit();
		}
	}
}

void MenuPlayer::Render(Renderer * _pRenderer)
{
	m_pStartText->Load(_pRenderer);
	m_pEndText->Load(_pRenderer);
}