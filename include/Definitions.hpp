#ifndef INCLUDED_ORBITAL_DEFINITIONS_HPP_
#define INCLUDED_ORBITAL_DEFINITIONS_HPP_

#include <zeno/Core/Vector2.hpp>
#include <zeno/Core/Rect.hpp>

namespace brk {

	template<typename T>
	struct vector2_hash_fxn {
		std::size_t operator()(const ze::Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};
	template<typename T>
	struct rect_hash_fxn {
		std::size_t operator()(const ze::Rect<T>& _rect) const {
			return  
				std::hash<T>()(_rect.left) ^
				std::hash<T>()(_rect.bot) ^
				std::hash<T>()(_rect.width) ^
				std::hash<T>()(_rect.height);
		}
	};

	class Definitions {
		Definitions() = delete;
		~Definitions() = delete;
	public:
		static constexpr const char Title[] = "Breakout";
		static constexpr const char Font_Midazzle_Name[] = "Midazzle";

		static constexpr const char Shader_Name_Sprite[] = "Shader_Name_Sprite";

		static constexpr float CellSize{ 1.0f };
		static constexpr float CellGap{ 0.1f };

		static int IntroSceneId;
		static int TitleSceneId;
		static int GameSceneId;
	};

}

#endif // INCLUDED_ORBITAL_DEFINITIONS_HPP_