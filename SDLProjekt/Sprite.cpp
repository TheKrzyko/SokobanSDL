#include "Sprite.h"


Sprite::Sprite()
{
	
}


Sprite::~Sprite()
{
}

void Sprite::setTexture(SDL_Texture* texture)
{
	frame.texture = texture;
	frame.rect.x = 0;
	frame.rect.y = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &(frame.rect.w), &(frame.rect.h));
}

SDL_Texture* Sprite::getTexture() const
{
	return frame.texture;
}

void Sprite::setFrame(const Frame frame)
{
	this->frame = frame;
}

Frame Sprite::getFrame() const
{
	return frame;
}



Vector2f Sprite::getLocalSize() const
{
	return Vector2f(frame.rect.w * scale.x, frame.rect.h * scale.y);
}

Vector2f Sprite::getGlobalSize() const
{
	return Vector2f(frame.rect.w, frame.rect.x);
}

void Sprite::draw(SDL_Renderer* renderer) const
{
	const SDL_RendererFlip flip = static_cast<SDL_RendererFlip>((scale.x >= 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL) | (
		scale.y >= 0 ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL));
	SDL_Rect dstRect = {
		position.x - origin.x * frame.rect.w*abs(scale.x),	//X	
		position.y - origin.y * frame.rect.h*abs(scale.x),	//Y
		frame.rect.w * abs(scale.x),			//W
		frame.rect.h * abs(scale.y)				//H
	};
	SDL_Point center = { origin.x * dstRect.w, origin.y * dstRect.h };

	SDL_RenderCopyEx(renderer, frame.texture, &(frame.rect), &dstRect, angle, &center, flip);
}
