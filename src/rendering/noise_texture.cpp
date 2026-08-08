#include "rendering/noise_texture.hpp"

#include "noise/noise.hpp"
#include "noise/function_registry.hpp"

#include <stdexcept>

NoiseTexture::NoiseTexture(int width, int height)
	: width_(width), height_(height), pixels_(width * height * 4)
{
	glGenTextures(1, &texture_id_);
	glBindTexture(GL_TEXTURE_2D, texture_id_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width_,
		height_,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		pixels_.data()
	);
}

NoiseTexture::~NoiseTexture() {
	if (texture_id_ != 0) {
		glDeleteTextures(1, &texture_id_);
		texture_id_ = 0;
	}
}

void NoiseTexture::Generate(const NoiseProject& project) {
	const Noise::Function source = Noise::Registry::GetFunction(project.function_type);

	Noise::Functions::NoiseParameters source_params{
		.x = 0.0f,
		.y = 0.0f,
		.seed = project.seed,
		.worley_distance_type = project.worley_distance,
		.worley_output_mode = project.worley_output
	};

	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < width_; ++x) {
			source_params.x = static_cast<float>(x) * project.scale;
			source_params.y = static_cast<float>(y) * project.scale;

			float value = 0.0f;
			
			if (project.fbm_params.octaves > 1) {
				value = Noise::Modifiers::FBM(
					source,
					source_params,
					project.fbm_params
				);
			}
			else {
				value = source(source_params);
			}

			const float normalized = value * 0.5f + 0.5f;	// All noise functions should return [-1, 1]

			if (normalized < 0.0f || normalized > 1.0f) {
				throw std::runtime_error("Noise value out of displayable range");
			}

			unsigned char gray = static_cast<unsigned char>(normalized * 255.0f);

			const int index = (y * width_ + x) * 4;

			pixels_[index + 0] = gray;
			pixels_[index + 1] = gray;
			pixels_[index + 2] = gray;
			pixels_[index + 3] = 255;
		}
	}
	
	glBindTexture(GL_TEXTURE_2D, texture_id_);

	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		0,
		0,
		width_,
		height_,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		pixels_.data()
	);
}

void NoiseTexture::Draw(ImVec2 size) const {
	ImGui::Image(
		static_cast<ImTextureID>(texture_id_),
		size
	);
}