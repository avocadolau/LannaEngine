#include "lnpch.h"
#include "GameObject.h"
#include <vector>

#include "Lanna/Log.h"
#include "Component.h"

#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/CameraComponent.h"

#include "Lanna/Application.h"
#include "Lanna/EntityManager.h"

#include <glew.h>
#include <glm.hpp>


namespace Lanna
{
	GameObject::GameObject(GameObject* copy)
	{
		m_Name = copy->m_Name;
		m_Name.append(" copy");

		if (copy->m_Transform)
		{
			m_Transform = new TransformComponent(copy->m_Transform);
			m_Components.push_back(m_Transform);
		}
		if (copy->m_Material) {
			m_Material = new MaterialComponent(copy->m_Material);
			m_Components.push_back(m_Material);
		}
		if (copy->m_Mesh) {
			m_Mesh = new MeshComponent(copy->m_Mesh);
			m_Components.push_back(m_Mesh);
		}
		if (copy->m_Camera &&m_Transform) {
			m_Camera = new CameraComponent(copy->m_Camera, m_Transform);
			m_Components.push_back(m_Camera);
		}
		
		for (GameObject* c : copy->m_Children)
		{
			AddCopyChild(c);
		}
	}
	GameObject::GameObject(const char* name) :m_Name(name)
	{
		AddComponent(Component::Type::TRANSFORM);
		std::string text = "";
		text= "Game object '" + (std::string)name + "' created";
		LN_TRACE(text.c_str());
	}
	GameObject::~GameObject()
	{
		delete m_Transform;
		m_Components.clear();
		m_Children.clear();
	}


	void GameObject::Update() {


		for (Component* c : m_Components)
		{
			c->Use();
		}
		for (GameObject* o : m_Children)
		{
			o->Update();
		}
		m_Transform->changed = false;
	}
	void GameObject::Render() {
		if (m_Mesh)
		{
			if (m_Mesh->m_MeshID != -1)
			{
				if (m_Material)
					LN_RENDERER.RenderMesh(LN_RESOURCES.GetResourceById<Mesh>(m_Mesh->m_MeshID), m_Transform->w_Pos, m_Transform->w_Rot, m_Transform->w_Scl, m_Material->getMaterial(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), false);
				else LN_RENDERER.RenderMeshColor(LN_RESOURCES.GetResourceById<Mesh>(m_Mesh->m_MeshID), m_Transform->w_Pos, m_Transform->w_Rot, m_Transform->w_Scl, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), false);

			}
		}
		for (GameObject* o : m_Children)
		{
			o->Render();
		}
	}

	Component* GameObject::AddComponent(Component::Type type)
	{
		switch (type)
		{
		case Component::Type::TOTAL:
			break;
		case Component::Type::TRANSFORM:
			if (m_Transform == nullptr)
			{
				m_Transform = new TransformComponent();
				m_Components.push_back(m_Transform);
				return m_Transform;
			}
			else
			{
				LN_INFO("Already has transform component");
			}
			break;
		case Component::Type::MESH:
			if (m_Mesh == nullptr)
			{
				m_Mesh = new MeshComponent();
				m_Components.push_back(m_Mesh);
				return m_Mesh;
			}
			else
			{
				LN_INFO("Already has mesh component");
			}
			break;
		case Component::Type::MATERIAL:
			if (m_Material == nullptr)
			{
				m_Material = new MaterialComponent();
				m_Components.push_back(m_Material);
				return m_Material;
			}
			else
			{
				LN_INFO("Already has material component");
			}
			break;
		case Component::Type::CAMERA:
			if (m_Camera == nullptr)
			{
				if (m_Transform == nullptr) AddComponent(Component::Type::TRANSFORM);
				//m_Camera = new CameraComponent(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), YAW, PITCH);
				m_Camera = new CameraComponent(m_Transform);
				m_Components.push_back(m_Camera);
				loockComonents = true;
				return m_Camera;
			}
			else
			{
				LN_INFO("Already has camera component");
			}
			break;
		}
		return nullptr;
	}

	void GameObject::AddCopyChild(GameObject* child)
	{
		GameObject* nChild= new GameObject(child);
		nChild->m_Parent = this;
		nChild->m_Transform->parent = m_Transform;
		m_Children.push_back(nChild);
	}

	void GameObject::AddEmptyChild()
	{
		GameObject* nChild = new GameObject("empty");
		nChild->m_Parent = this;
		nChild->m_Transform->parent = m_Transform;
		m_Children.push_back(nChild);
	}

	void GameObject::DelChild(GameObject* child)
	{
		
		int pos = 0;
		for (GameObject* o : m_Children)
		{
			if (o == child)
			{
				m_Children.at(pos) = nullptr;
				auto it = std::find(m_Children.begin(), m_Children.end(), nullptr);
				m_Children.erase(it);
				o->m_Parent = nullptr;
				LN_ENTITY_MAN->AddGameObject(o);
				break;
			}
			else
			{
				pos++;
			}
		}


	}

	void GameObject::DestroyChild(GameObject* child)
	{
		auto it = std::find(m_Children.begin(), m_Children.end(), child);
		if (it != m_Children.end())
		{
			m_Children.erase(it);
			delete child;
			child = nullptr;
		}

	}

	void GameObject::DestroyComponent(Component* comp)
	{
		auto it = std::find(m_Components.begin(), m_Components.end(), comp);
		if (it != m_Components.end())
		{
			m_Components.erase(it);
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Reparent(GameObject* newParent)
	{
		if (m_Parent)
		{
			m_Parent->DelChild(this);
		}
		else
		{
			LN_ENTITY_MAN->DeleteGameObject(this);
		}
		newParent->m_Children.push_back(this);
		m_Parent = newParent;
	}


}