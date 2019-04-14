#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void dae::ResourceManager::Init(std::string&& dataPath)
{
	mDataPath = std::move(dataPath);

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file, UINT id)
{
	UNREFERENCED_PARAMETER(id);
	//TODO: ADD ID MATCH TO TEXTURE LOADING
	std::string fullPath = mDataPath + file;
	SDL_Texture *texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	auto pTex = std::make_shared<Texture2D>(texture);

	for (std::pair<UINT, std::shared_ptr<Texture2D>> materialEntry : m_pLoadedTextures)
	{
		if (materialEntry.first == id)
		{
			std::cout << "ResourceManager::LoadTexture() > id %i is already used! " << id << '\n';
			return nullptr;
		}

		if (materialEntry.second == pTex)
		{
			std::cout << "ResourceManager::LoadTexture() > Texture is already added to the manager (ID %i)! " << id << '\n';
			return nullptr;
		}
	}
	m_pLoadedTextures[id] = pTex;
	return pTex;
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(mDataPath + file, size);
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::GetTexture(UINT id)
{
	const auto it = m_pLoadedTextures.find(id);
	if (it == m_pLoadedTextures.end())
	{
		std::cout << "ResourceManager::LoadTexture() > Material with ID %i not found! " << id << '\n';
		return nullptr;
	}
	return it->second;
}
