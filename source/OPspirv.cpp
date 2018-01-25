#include "OPspirv.h"

#include "./Core/include/OPlog.h"
#include "./Data/include/OPcman.h"
#include "./Human/include/Rendering/OPshader.h"

#include "spirv_glsl.hpp"
#include <vector>
#include <utility>

OPint OPloaderOPspvLoad(OPstream* str, OPshader** shader) {
    OPlogErr("Loading SPV %d", str->Size);


	spirv_cross::CompilerGLSL glsl((uint32_t*)str->Data, (str->Size / 4)); //(std::move(str->Buffer));

	// The SPIR-V is now parsed, and we can perform reflection on it.
	spirv_cross::ShaderResources resources = glsl.get_shader_resources();

	// Get all sampled images in the shader.
	for (auto &resource : resources.sampled_images)
	{
		unsigned set = glsl.get_decoration(resource.id, spv::DecorationDescriptorSet);
		unsigned binding = glsl.get_decoration(resource.id, spv::DecorationBinding);
		printf("Image %s at set = %u, binding = %u\n", resource.name.c_str(), set, binding);

		// Modify the decoration to prepare it for GLSL.
		glsl.unset_decoration(resource.id, spv::DecorationDescriptorSet);

		// Some arbitrary remapping if we want.
		glsl.set_decoration(resource.id, spv::DecorationBinding, set * 16 + binding);
	}

	// Set some options.
	spirv_cross::CompilerGLSL::Options options;
	options.version = 310;
	options.es = true;
	glsl.set_options(options);

	// Compile to GLSL, ready to give to GL driver.
	std::string source = glsl.compile();

    OPlogErr("Shader Result: %s", source.c_str());

    return 1;
}

OPint OPloaderOPspvUnload(OPshader* shader) {
    return 1;
}

void OPsprivAddLoader() {
	OPassetLoader loader = {
		".spv",
		"SPV/",
		sizeof(OPshader),
		(OPint(*)(OPstream*, void**))OPloaderOPspvLoad,
		(OPint(*)(void*))OPloaderOPspvUnload,
		NULL
	};
	OPCMAN.AddLoader(&loader);
}