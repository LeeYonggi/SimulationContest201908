#pragma once


//define

#define ELTime DXUTGetElapsedTime() * timeScale
#define DEVICE DXUTGetD3D9Device()
#define SCREEN_X 1280
#define SCREEN_Y 720
#define HASH(key) GetHashCode(key)

using Color	  = D3DXCOLOR;
using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Matrix  = D3DXMATRIX;

extern float timeScale;


//include

#include "Utility.h"

#include "Singleton.h"

#include "ResourceManager.h"

#include "RenderManager.h"

#include "CameraManager.h"

#include "Scene.h"

#include "SceneManager.h"

#include "Animator.h"

#include "InputManager.h"

#include "GameObject.h"

#include "ObjectManager.h"

#include "GameManager.h"

#include "CharacterState.h"

#include "Character.h"

#include "Gun.h"

#include "MainProc.h"