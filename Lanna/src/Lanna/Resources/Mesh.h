#pragma once
#include "Lanna/Resources/Framebuffer.h"
//#include "Lanna/Resources/Material.h"
#include "Lanna/Utilities/Maths/AABB.h"
#include "lnpch.h"

enum PrimitivesMesh {
	CUBE,
	PYRAMID,
	PLANE,

	TOTAL
};

struct aiMesh;

namespace Lanna {

	struct VertexBoneData
	{
		unsigned int IDs[MAX_BONES_PER_VERTEX];
		float weights[MAX_BONES_PER_VERTEX];
	};

	class Mesh
	{
	public:
		Mesh();
		Mesh(const char* file);
		~Mesh();

		void LoadFromFile(const char* file);
		void LoadPrimitive(PrimitivesMesh primitive);
		void Render();
		Mesh* loadmesh(const aiMesh* mesh);

		void Save(const char* path);
		void Load(const char* path);

	private:
		void GenerateBuffers();
		unsigned int GetModelsSize();
	public:
		unsigned int vao = -1;				// vertex array object
		unsigned int ebo = -1;				// element buffer object
		unsigned int vbo = -1;				// vertex buffer object

		std::vector<float> vbo_data;
		std::vector<int> ebo_data;
		std::vector<Mesh*> models;
		std::vector<VertexBoneData*> boneWeights;

		Lanna::Framebuffer* buff;
		bool is_root = false;
		AABB aabb;
		bool hasBones = false;

	};

}