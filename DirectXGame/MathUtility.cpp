#include "mathUtility.h"

Matrix4x4 MatrixMultipry(const Matrix4x4& matrix1, const Matrix4x4& matrix2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {

		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = matrix1.m[i][0] * matrix2.m[0][j] + matrix1.m[i][1] * matrix2.m[1][j] + matrix1.m[i][2] * matrix2.m[2][j] + matrix1.m[i][3] * matrix2.m[3][j];
		}
	}

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate) {

	// エラー対策(使用しない)
	Vector3 dm = scale;

	// 回転
	Matrix4x4 RotateMatY = {cosf(rot.y), 0, -sinf(rot.y), 0, 0, 1, 0, 0, sinf(rot.y), 0, cosf(rot.y), 0, 0, 0, 0, 1};

	// 平行移動行列の作成
	Matrix4x4 TranslateMat = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, translate.x, translate.y, translate.z, 1};

	// 回転*平行移動だけをワールド変換行列に
	Matrix4x4 ansMat = MatrixMultipry(RotateMatY, TranslateMat);

	return ansMat;
}

Matrix4x4 MakeRotateZMatrix(float angle) {
	Matrix4x4 matrix;

	float cosAngle = std::cos(angle);
	float sinAngle = std::sin(angle);

	matrix.m[0][0] = cosAngle;
	matrix.m[0][1] = -sinAngle;
	matrix.m[0][2] = 0.0f;
	matrix.m[0][3] = 0.0f;

	matrix.m[1][0] = sinAngle;
	matrix.m[1][1] = cosAngle;
	matrix.m[1][2] = 0.0f;
	matrix.m[1][3] = 0.0f;

	matrix.m[2][0] = 0.0f;
	matrix.m[2][1] = 0.0f;
	matrix.m[2][2] = 1.0f;
	matrix.m[2][3] = 0.0f;

	matrix.m[3][0] = 0.0f;
	matrix.m[3][1] = 0.0f;
	matrix.m[3][2] = 0.0f;
	matrix.m[3][3] = 1.0f;

	return matrix;
}

Vector3 Transform(const Vector3& vec, const Matrix4x4& mat) {
	Vector3 result;

	result.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0];
	result.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1];
	result.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2];

	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 subtract;
	subtract.x = (v1.x - v2.x);
	subtract.y = (v1.y - v2.y);
	subtract.z = (v1.z - v2.z);
	return subtract;
}

Vector3 Normalize(const Vector3& v) {

	float len = KamataEngine::MathUtility::Length(v);
	Vector3 v2 = {};
	v2.x = v.x / len;
	v2.y = v.y / len;
	v2.z = v.z / len;

	return v2;
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 m = {};
	m.m[0][0] = scale.x;
	m.m[1][1] = scale.y;
	m.m[2][2] = scale.z;
	m.m[3][3] = 1;
	return m;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 m = {};
	m.m[0][0] = 1;
	m.m[1][1] = 1;
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	m.m[3][0] = translate.x;
	m.m[3][1] = translate.y;
	m.m[3][2] = translate.z;
	return m;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 m = {};
	m.m[0][0] = 2 / (right - left);
	m.m[1][1] = 2 / (top - bottom);
	m.m[2][2] = 1 / (farClip - nearClip);
	m.m[3][0] = -(right + left) / (right - left);
	m.m[3][1] = -(top + bottom) / (top - bottom);
	m.m[3][2] = -nearClip / (farClip - nearClip);
	m.m[3][3] = 1;
	return m;
}

Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 m = {};
	m.m[0][0] = width / 2;
	m.m[1][1] = -height / 2;
	m.m[2][2] = maxDepth - minDepth;
	m.m[3][0] = left + width / 2;
	m.m[3][1] = top + height / 2;
	m.m[3][2] = minDepth;
	m.m[3][3] = 1;
	return m;
}

Matrix4x4 MakePerspectiveMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 m = {};
	float yScale = 1 / std::tan(fovY / 2);
	float xScale = yScale / aspectRatio;
	m.m[0][0] = xScale;
	m.m[1][1] = yScale;
	m.m[2][2] = farClip / (farClip - nearClip);
	m.m[2][3] = 1;
	m.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	m.m[3][3] = 0;
	return m;
}

Vector3& operator*=(Vector3& v, float s) {
	v.x *= s;
	v.y *= s;
	v.z *= s;

	return v;
}

Vector3 operator*(const Vector3& v, float s) {
	Vector3 temp(v);
	return temp *= s;
}

Vector3& operator+=(Vector3& lhv, const Vector3& rhv) {
	lhv.x += rhv.x;
	lhv.y += rhv.y;
	lhv.z += rhv.z;

	return lhv;
}

Vector3& operator-=(Vector3& lhv, const Vector3& rhv) {
	lhv.x -= rhv.x;
	lhv.y -= rhv.y;
	lhv.z -= rhv.z;

	return lhv;
}

const Vector3 operator-(Vector3& v1, Vector3& v2) { return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z}; }