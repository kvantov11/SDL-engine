#pragma once

#include <memory>
#include <vector>

#define M3UpRotation(radians) { std::cos(radians), -std::sin(radians), 0.f }, { std::sin(radians), std::cos(radians), 0.f }, { 0.f, 0.f, 1.f }
#define M3RightRotation(radians) { std::cos(radians), 0.f, std::sin(radians) }, { 0.f, 1.f, 0.f }, { -std::sin(radians), 0.f, std::cos(radians) }
#define M3ForwardRotation(radians) { 1.f, 0.f, 0.f }, { 0.f, std::cos(radians), -std::sin(radians) }, { 0.f, std::sin(radians), std::cos(radians) }

class Vector3
{
private:
	float _elements[3]{ 0.f, 0.f, 0.f };
public:
	Vector3() = default;
	Vector3(const float x, const float y, const float z);
	float GetElement(const unsigned int element) const;
	void SetElement(const unsigned int element, const float value);
	float DotProduct(const Vector3& vector) const;
};

class Vector4
{
private:
	float _elements[4]{ 0.f, 0.f, 0.f, 0.f };
public:
	Vector4() = default;
	Vector4(const float x, const float y, const float z, const float k);
	Vector4(const Vector3& vector, const float k);
	float GetElement(const unsigned int element) const;
	void SetElement(const unsigned int element, const float value);
	float DotProduct(const Vector4& vector) const;
};

class Matrix3x3
{
private:
	Vector3 _vectors[3]{ 
		{0.f, 0.f, 0.f}, 
		{0.f, 0.f, 0.f}, 
		{0.f, 0.f, 0.f} };
public:
	Matrix3x3() = default;
	Matrix3x3(const Vector3& A, const Vector3& B, const Vector3& C);
	Vector3 GetRow(const unsigned int row) const;
	void SetRow(const unsigned int row, const Vector3& vector);
	Vector3 GetColumn(const unsigned int column) const;
	void SetColumn(const unsigned int column, const Vector3& vector);
	float GetElement(const unsigned int row, const unsigned int column) const;
	void SetElement(const unsigned int row, const unsigned int column, const float value);
	void Transpose();
	Matrix3x3 GetTransposed() const;
	Vector3 Multiply(const Vector3& vector) const;
	Matrix3x3 Multiply(const Matrix3x3& matrix) const;
};

class Matrix4x4
{
private:
	Vector4 _vectors[4]{
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f} };
public:
	Matrix4x4() = default;
	Matrix4x4(const Vector4& A, const Vector4& B, const Vector4& C, const Vector4& D);
	Vector4 GetRow(const unsigned int row) const;
	void SetRow(const unsigned int row, const Vector4& vector);
	Vector4 GetColumn(const unsigned int column) const;
	void SetColumn(const unsigned int column, const Vector4& vector);
	float GetElement(const unsigned int row, const unsigned int column) const;
	void SetElement(const unsigned int row, const unsigned int column, const float value);
	void Transpose();
	Matrix4x4 GetTransposed() const;
	Vector4 Multiply(const Vector4& vector) const;
	Matrix4x4 Multiply(const Matrix4x4& matrix) const;
};

class Transform
{
private:
	Vector3 _position{ 0.f, 0.f, 0.f };
	Vector3 _forward{ 1.0f, 0.f, 0.f };
	Vector3 _right{ 0.f, 1.f, 0.f };
	Vector3 _up{ 0.f, 0.f, 1.f };
public:
	static Transform Multiply(const Transform& A, const Transform& B);
	static Vector4 Multiply(const Transform& transform, const Vector4& vector);
	static Vector3 Multiply(const Transform& transform, const Vector3& vector);
public:
	Transform() = default;
	Transform(const Matrix4x4& matrix);
	Vector3 GetPosition() const;
	void SetPosition(const Vector3& position);
	Matrix3x3 GetOrientation() const;
	void SetOrientation(const Matrix3x3& orientation);
	Vector3 GetForwardVector() const;
	void SetForwardVector(const Vector3& forward);
	Vector3 GetRightVector() const;
	void SetRightVector(const Vector3& right);
	Vector3 GetUpVector() const;
	void SetUpVector(const Vector3& up);
	void RotateForwardAxis(const float angle);
	void RotateRightAxis(const float angle);
	void RotateUpAxis(const float angle);
	void TranslateForward(const float distance);
	void TranslateRight(const float distance);
	void TranslateUp(const float distance);
	void Translate(const float forward, const float right, const float up);
	void Translate(const Vector3& vector);
	Matrix4x4 GetTransformMatrix() const;
};

class Object
{
private:
	Transform _transformGlobal;
	Transform _transformLocal;
	std::vector<std::weak_ptr<Object>> _attachedObjects;
	std::weak_ptr<Object> _parentPtr;
public:
	static void AttachToParent(std::weak_ptr<Object> parentPtr, std::weak_ptr<Object> childPtr);
public:
	const Transform& GetTransformGlobal() const;
	void SetTransformGlobal(const Transform& transform);
	Transform& TransformGlobal();
	const Transform& GetTransformLocal() const;
	void SetTransformLocal(const Transform& transform);
	Transform& TransformLocal();

	const std::vector<std::weak_ptr<Object>>& GetAttachedObjects() const;
	const std::weak_ptr<Object> GetParent() const;
private:
	void AttachChild(std::weak_ptr<Object> childPtr);
	void SetParent(std::weak_ptr<Object> parentPtr);
};