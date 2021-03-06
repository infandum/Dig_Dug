#pragma once
namespace dae
{
	class Texture2D;
	class Font;
	class ResourceManager final
	{
		
	public:
		ResourceManager() = default;

		void Init(std::string&& data);

		void LoadTexture(const std::string& file, UINT id);
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

		std::shared_ptr<Texture2D> GetTexture(UINT id);
	private:
		std::string mDataPath;
		std::map<UINT, std::shared_ptr<Texture2D>> m_pLoadedTextures;
	};

}
