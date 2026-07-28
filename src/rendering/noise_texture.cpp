#include "noise_texture.hpp"
#include "noise_utils.hpp"

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

void NoiseTexture::Generate(
	const Noise::Generator& generator,
	float scale
) {
	for (int y = 0; y < height_; ++y) {
		for (int x = 0; x < width_; ++x) {
			float nx = static_cast<float>(x) * scale;
			float ny = static_cast<float>(y) * scale;

			float value = generator.Sample(nx, ny); // [-1, 1]
			float display = Noise::Math::Clamp(
				value * 0.5f + 0.5f,
				0.0f,
				1.0f
			);

			unsigned char gray = static_cast<unsigned char>(display * 255.0f);

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