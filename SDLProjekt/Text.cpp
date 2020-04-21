#include "Text.h"
#include "Game.h"


Text::Text()
{
	setColor(Color(255, 255, 255));
	background.setColor(Color(0,0,0,0));
}


Text::~Text()
{
	if (buffor != nullptr)
		SDL_FreeSurface(buffor);
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

String Text::getString() const
{
	return string;
}

void Text::setString(const String& str, SDL_Renderer* renderer)
{
	string = str;
	int textLength = string.getSize();
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
	SDL_Surface* buffor = SDL_CreateRGBSurface(0, charSize.x*textLength, charSize.y, 32, 0, 0, 0, 0);
	SDL_SetColorKey(buffor, SDL_TRUE, 0);
	int px, py;
	SDL_Rect source, dest;
	source.w = charSize.x;
	source.h = charSize.y;
	dest.w = charSize.x;
	dest.h = charSize.y;
	int rows = (charsetSize.y / charSize.y);
	int cols = (charsetSize.x / charSize.x);
	for (int i = 0; i < textLength; i++)
	{
		px = (string[i] % cols) * charSize.x;
		py = (string[i] / rows) * charSize.y;

		source.x = px;
		source.y = py;
		dest.x = i*charSize.x;
		dest.y = 0;

		SDL_BlitSurface(charset, &source, buffor, &dest);
	}
	texture = SDL_CreateTextureFromSurface(renderer, buffor);
	SDL_FreeSurface(buffor);
}

void Text::setCharset(SDL_Surface* charset, Vector2i charSize, Vector2i charsetSize)
{
	this->charset = charset;
	this->charSize = charSize;
	this->charsetSize = charsetSize;
}

void Text::setColor(Color color)
{
	this->color = color;
}

void Text::setBackgroundColor(Color color)
{
	background.setColor(color);
}

void Text::setOffset(int off)
{
	offset = off;
}

Color Text::getColor()
{
	return color;
}

MyRect Text::getBounds()
{
	return MyRect((int)floor(position.x - origin.x*abs(scale.x)*charSize.x*string.getSize()), (int)floor(position.y - origin.y*scale.y*charSize.y), (int)ceil(charSize.x*string.getSize()*abs(scale.x)), (int)ceil(charSize.y*abs(scale.y)));
}

void Text::draw(SDL_Renderer* renderer)
{
	const SDL_RendererFlip flip = static_cast<SDL_RendererFlip>((scale.x >= 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL) | (
		scale.y >= 0 ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL));
	
	SDL_Rect srcRect = {
		0,
		0,
		charSize.x*string.getSize(),
		charSize.y
	};
	SDL_Rect dstRect = {
		position.x - origin.x * srcRect.w*abs(scale.x),	//X	
		position.y - origin.y * srcRect.h*abs(scale.y),	//Y
		srcRect.w*abs(scale.x),				//W
		srcRect.h*abs(scale.y)				//H
	};
	SDL_Point center = { origin.x * dstRect.w, origin.y * dstRect.h };
	background.setPosition(position);
	background.setSize(getBounds().w+ offset, getBounds().h+ offset);
	background.draw(renderer);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle, &center, flip);
	SDL_FreeSurface(buffor);
}
