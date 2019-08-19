#pragma once


//define

#define ELTime DXUTGetElapsedTime() * timeScale
#define DEVICE DXUTGetD3D9Device()
#define SCREEN_X 1280
#define SCREEN_Y 720

using Color	  = D3DXCOLOR;
using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Matrix  = D3DXMATRIX;

extern float timeScale;


//include

#include "Utility.h"

#include "Singleton.h"

#include "InputManager.h"

#include "ResourceManager.h"

#include "RenderManager.h"

#include "CameraManager.h"

#include "Scene.h"

#include "SceneManager.h"

#include "Animator.h"

#include "GameObject.h"

#include "ObjectManager.h"

#include "Character.h"

#include "MainProc.h"