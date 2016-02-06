#include "Player.h"
#include "Game.h"
#include <string>
#include "Camera.h"
#include "AudioManager.h"

Player::~Player()
{
}

Player::Player() : LivingEntity()
{
	position.X = 0;
	maxVel = Vector2D(10, 15);
	acceleration = Vector2D(1, 1);	
	SetJump(-15);
	lives = 3;
	setOnCollide(([](Entity * player, Entity * another) {
		Player * p = (Player *)player;
		if (another == NULL) {
			return;
		}
		if (Enemy * enemy = dynamic_cast<Enemy *>(another))
		{
			if (p->invulnerable == 0)
			{
				p->lives--;
				if (p->lives == 0)
				{
					Audio->SetVolume(64);
					Audio->PlaySound("nazgul");
					TheGame->GameOver();
				}
				p->invulnerable = 180;
				p->Damage();
				another->onCollide(p);
			}
		}
		else if (Player * pl = dynamic_cast<Player *>(another)) {
			return;
		}
		else {
			another->onCollide(p);
		}
	}));
}

void Player::Damage()
{
	velocity.Y = salt;
	Audio->PlaySound("damage");
}

void Player::unStuck()
{
	if (LivingEntity::IsCollidingWithTile(position.X, position.Y)) {
		position.Y -= params->GetHeight();
	}
}

void Player::Load(EntityParams * params)
{
	LivingEntity::Load(params);
}

void Player::Update()
{
	if (invulnerable > 0)
	{
		invulnerable--;
	}
	if (position.Y > Tools::GetHeight())
	{
		onVoid();
	}
	Accelerate(xAccel, yAccel);	
	LivingEntity::Update();	
}

bool Player::InBounds(LivingEntity * entitat)
{
	return Tools::InBounding(entitat, this);
}

void Player::Jump()
{
	if (!inAir) {
		velocity.Y = salt;
		Audio->PlaySound("jump");
	}		
}

void Player::DrawFrame()
{
	SDL_Rect img, draw;

	img.x = params->GetWidth() * params->GetFrame();
	img.y = params->GetHeight() * params->GetRow();
	img.w = params->GetWidth();
	img.h = params->GetHeight();

	draw.x = (int)position.X - (int)TheCam->GetPosition()->X;
	draw.y = (int)position.Y - (int)TheCam->GetPosition()->Y;
	draw.w = params->GetWidth();
	draw.h = params->GetHeight();

	SDL_RendererFlip flip = params->IsFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

	SDL_Texture * textura = TextureManager::GetInstance()->GetArray()[texture];
	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), textura, &img, &draw, 0, NULL, flip);
}

void Player::onVoid()
{
	if (invulnerable > 0)
		return;
	lives--;
	if (lives == -1)
	{
		Audio->SetVolume(64);
		Audio->PlaySound("nazgul");
		TheGame->GameOver();
	}
	invulnerable = 15;
}