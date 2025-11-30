#pragma once
#include <entt/entity/entity.hpp>

#include "Components.h"
#include "Scene.h"
#include "Core/Log.h"
#include "glm/vec2.hpp"
#include "AssetManager/IAssetManager.h"


namespace Spyen {
	class Entity
	{
	public:
		Entity(entt::entity handle, Scene* parent_scene) : m_EntityHandle(handle), m_ParentScene(parent_scene) {};
		~Entity() = default;

		template<typename TComponent, typename... Args>
		void AddComponent(Args&&... args)
		{
			if (m_ParentScene->m_Registry.any_of<TComponent>(m_EntityHandle))
			{
				SPY_CORE_ERROR("Entity already has this component!");
				return;
			}

			m_ParentScene->m_Registry.emplace<TComponent>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename TComponent>
		void RemoveComponent() const {
			m_ParentScene->m_Registry.remove<TComponent>(m_EntityHandle);
		}

		template<typename TComponent>
		[[nodiscard]] bool HasComponent() const {
			return m_ParentScene->m_Registry.all_of<TComponent>(m_EntityHandle);
		}

		template<typename TComponent>
		TComponent& GetComponent() {
			if (!HasComponent<TComponent>()) {
				SPY_CORE_ERROR("Entity does not have this component!");
				throw std::runtime_error("Component does not exist");
			}
			return m_ParentScene->m_Registry.get<TComponent>(m_EntityHandle);
		}


		/*virtual void OnInit() = 0;
		virtual void OnUpdate() = 0;*/

		////////////////////////////////////////////////////////////////////////////////////////////
		//		  _   _      _                  ______                _   _						  //
		//		 | | | |    | |                 |  ___|              | | (_)					  //
		//	 	 | |_| | ___| |_ __  ___ _ __   | |_ _   _ _ __   ___| |_ _  ___  _ __  ___       //
		//	  	 |  _  |/ _ \ | '_ \/ _ \ '__|  |  _| | | | '_ \ / __| __| |/ _ \| '_ \ / __|     //
		//		 | | | |  __/ | |_) | __/ |     | | | |_| | | | | (__| |_| | (_) | | | \__ \      //
		//		 \_| |_/\___|_| .__/\___|_|     \_| \__,__|_| |_|\___|\__|_|\___/|_| |_| ___/     //
		//					  | |																  //
		//			          |_|																  //
		////////////////////////////////////////////////////////////////////////////////////////////

		/// <summary>
		/// Sets the position of the entity
		/// </summary>
		/// <param name="pos">the position as a vec2</param>
		inline void SetPosition(const glm::vec2& pos)
		{
			GetComponent<TransformComponent>().Position = pos;
		}

		/// <summary>
		/// Gets the position of the entity
		/// </summary>
		/// <returns>the position as a vec2</returns>
		inline glm::vec2 GetPosition()
		{
			return GetComponent<TransformComponent>().Position;
		}

		/// <summary>
		/// Sets the rotation of the entity
		/// </summary>
		/// <param name="rot">the rotation in degrees as a float</param>
		inline void SetRotation(float rot)
		{
			GetComponent<TransformComponent>().Rotation = rot;
		}

		/// <summary>
		/// Gets the rotation of the entity
		/// </summary>
		/// <returns>the rotation in degrees as a float</returns>
		inline float GetRotation()
		{
			return GetComponent<TransformComponent>().Rotation;
		}

		/// <summary>
		/// Sets the scale of the entity
		/// </summary>
		/// <param name="scale">the scale as a vec2 where the parameters are the scale on the x and y-axis</param>
		inline void SetScale(const glm::vec2& scale)
		{
			GetComponent<TransformComponent>().Scale = scale;
		}

		/// <summary>
		/// Gets the scale of the entity
		/// </summary>
		/// <returns>the scale as a vec2 where the parameters are the scale on the x and y-axis</returns>
		inline glm::vec2 GetScale()
		{
			return GetComponent<TransformComponent>().Scale;
		}

		/// <summary>
		/// Sets the texture of the entity
		/// </summary>
		/// <param name="texture">a texture ptr from the AssetManager</param>
		inline void SetTexture(Texture* texture)
		{
			GetComponent<RenderComponent>().Texture = texture;
		}

		/// <summary>
		/// Sets the texture of the entity
		/// </summary>
		/// <param name="path">the path of the texture</param>
		inline void SetTexture(const std::filesystem::path& path) {
			IAssetManager::LoadTexture(path);
		}

		/// <summary>
		/// Sets the color of the entity
		/// </summary>
		/// <param name="red">the red value in the range 0-255</param>
		/// <param name="green">the green value in the range 0-255</param>
		/// <param name="blue">the blue value in the range 0-255</param>
		inline void SetColor(uint8_t red, uint8_t green, uint8_t blue)
		{
			GetComponent<RenderComponent>().Color = {static_cast<float>(red) / 255.f, static_cast<float>(green) / 255.f, static_cast<float>(blue) / 255.f};
		}

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_ParentScene == other.m_ParentScene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity m_EntityHandle;
		Scene* m_ParentScene = nullptr;
	};

}
