#define _USE_MATH_DEFINES
#include "randomstuff.h"

#include <cmath>

Vector3::Vector3(const float x, const float y, const float z)
{
    _elements[0] = x;
    _elements[1] = y;
    _elements[2] = z;
}

float Vector3::GetElement(const unsigned int element) const
{
    return _elements[element];
}

void Vector3::SetElement(const unsigned int element, const float value)
{
    _elements[element] = value;
}

float Vector3::DotProduct(const Vector3& vector) const
{
    return {
        this->_elements[0] * vector._elements[0] +
        this->_elements[1] * vector._elements[1] +
        this->_elements[2] * vector._elements[2] };
}

Vector4::Vector4(const float x, const float y, const float z, const float k)
{
    _elements[0] = x;
    _elements[1] = y;
    _elements[2] = z;
    _elements[3] = k;
}

Vector4::Vector4(const Vector3& vector, const float k)
{
    for (int i = 0; i < 3; ++i)
    {
        _elements[i] = vector.GetElement(i);
    }
    
    _elements[3] = k;
}

float Vector4::GetElement(const unsigned int element) const
{
    return _elements[element];
}

void Vector4::SetElement(const unsigned int element, float value)
{
    _elements[element] = value;
}

float Vector4::DotProduct(const Vector4& vector) const
{
    return {
        this->_elements[0] * vector._elements[0] +
        this->_elements[1] * vector._elements[1] +
        this->_elements[2] * vector._elements[2] +
        this->_elements[3] * vector._elements[3] };
}

Matrix3x3::Matrix3x3(const Vector3& A, const Vector3& B, const Vector3& C)
{
    _vectors[0] = A;
    _vectors[1] = B;
    _vectors[2] = C;
}

Vector3 Matrix3x3::GetRow(const unsigned int row) const
{
    return _vectors[row];
}

void Matrix3x3::SetRow(const unsigned int row, const Vector3& vector)
{
    _vectors[row] = vector;
}

Vector3 Matrix3x3::GetColumn(const unsigned int column) const
{
    Vector3 result;
    for (int i = 0; i < 3; ++i)
    {
        result.SetElement(i, _vectors[i].GetElement(column));
    }

    return result;
}

void Matrix3x3::SetColumn(const unsigned int column, const Vector3& vector)
{
    for (int i = 0; i < 3; ++i)
    {
        _vectors[i].SetElement(column, vector.GetElement(i));
    }
}

float Matrix3x3::GetElement(const unsigned int row, const unsigned int column) const
{
    return _vectors[row].GetElement(column);
}

void Matrix3x3::SetElement(const unsigned int row, const unsigned int column, const float value)
{
    _vectors[row].SetElement(column, value);
}

void Matrix3x3::Transpose()
{
    float temp{ 0 };
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        { 
            if (i != j)
            {
                temp = _vectors[i].GetElement(j);
                _vectors[i].SetElement(j, _vectors[j].GetElement(i));
                _vectors[j].SetElement(i, temp);
            }
        }
    }
}

Matrix3x3 Matrix3x3::GetTransposed() const
{
    Matrix3x3 matrix(*this);
    matrix.Transpose();
    return matrix;
}

Vector3 Matrix3x3::Multiply(const Vector3& vector) const
{
    Vector3 result;
    for (int i = 0; i < 3; ++i)
    {
        result.SetElement(i, _vectors[i].DotProduct(vector));
    }

    return result;
}

Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& matrix) const
{
    Matrix3x3 result;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            result.SetElement(i, j, _vectors[i].DotProduct(matrix.GetColumn(j)));
        }
    }

    return result;
}

Transform Transform::Multiply(const Transform& A, const Transform& B)
{
    return A.GetTransformMatrix().Multiply(B.GetTransformMatrix());
}

Vector4 Transform::Multiply(const Transform& transform, const Vector4& vector)
{
    return transform.GetTransformMatrix().Multiply(vector);
}

Vector3 Transform::Multiply(const Transform& transform, const Vector3& vector)
{
    Vector4 multiplier{ vector, 1.f };
    Vector4 result{ Transform::Multiply(transform,multiplier) };
    return { result.GetElement(0), result.GetElement(1), result.GetElement(2) };
}

Transform::Transform(const Matrix4x4& matrix)
{
    for (int i = 0; i < 3; ++i)
    {
        _forward.SetElement(i, matrix.GetRow(0).GetElement(i));
        _right.SetElement(i, matrix.GetRow(1).GetElement(i));
        _up.SetElement(i, matrix.GetRow(2).GetElement(i));
        _position.SetElement(i, matrix.GetColumn(3).GetElement(i));
    }
}

Vector3 Transform::GetPosition() const
{
    return _position;
}

void Transform::SetPosition(const Vector3& position)
{
    _position = position;
}

Matrix3x3 Transform::GetOrientation() const
{
    return Matrix3x3(_forward, _right, _up);
}

Matrix4x4::Matrix4x4(const Vector4& A, const Vector4& B, const Vector4& C, const Vector4& D)
{
    _vectors[0] = A;
    _vectors[1] = B;
    _vectors[2] = C;
    _vectors[3] = D;
}

Vector4 Matrix4x4::GetRow(const unsigned int row) const
{
    return _vectors[row];
}

void Matrix4x4::SetRow(const unsigned int row, const Vector4& vector)
{
    _vectors[row] = vector;
}

Vector4 Matrix4x4::GetColumn(const unsigned int column) const
{
    Vector4 result;
    for (int i = 0; i < 4; ++i)
    {
        result.SetElement(i, _vectors[i].GetElement(column));
    }

    return result;
}

void Matrix4x4::SetColumn(const unsigned int column, const Vector4& vector)
{
    for (int i = 0; i < 4; ++i)
    {
        _vectors[i].SetElement(column, vector.GetElement(i));
    }
}

float Matrix4x4::GetElement(const unsigned int row, const unsigned int column) const
{
    return _vectors[row].GetElement(column);
}

void Matrix4x4::SetElement(const unsigned int row, const unsigned int column, const float value)
{
    _vectors[row].SetElement(column, value);
}

void Matrix4x4::Transpose()
{
    float temp{ 0 };
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (i != j)
            {
                temp = _vectors[i].GetElement(j);
                _vectors[i].SetElement(j, _vectors[j].GetElement(i));
                _vectors[j].SetElement(i, temp);
            }
        }
    }
}

Matrix4x4 Matrix4x4::GetTransposed() const
{
    Matrix4x4 matrix(*this);
    matrix.Transpose();
    return matrix;
}

Vector4 Matrix4x4::Multiply(const Vector4& vector) const
{
    Vector4 result;
    for (int i = 0; i < 4; ++i)
    {
        result.SetElement(i, _vectors[i].DotProduct(vector));
    }

    return result;
}

Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& matrix) const
{
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result.SetElement(i, j, _vectors[i].DotProduct(matrix.GetColumn(j)));
        }
    }

    return result;
}

void Transform::SetOrientation(const Matrix3x3& orientation)
{
    _forward = orientation.GetRow(0);
    _right = orientation.GetRow(1);
    _up = orientation.GetRow(2);
}

Vector3 Transform::GetForwardVector() const
{
    return _forward;
}

void Transform::SetForwardVector(const Vector3& forward)
{
    _forward = forward;
}

Vector3 Transform::GetRightVector() const
{
    return _right;
}

void Transform::SetRightVector(const Vector3& right)
{
    _right = right;
}

Vector3 Transform::GetUpVector() const
{
    return _up;
}

void Transform::SetUpVector(const Vector3& up)
{
    _up = up;
}

void Transform::RotateUpAxis(const float angle)
{
    const float radians = M_PI * (angle / 180.f);
    const Matrix3x3 rotationMatrix{ M3UpRotation(radians) };
    SetOrientation(rotationMatrix.Multiply({ _forward, _right, _up }));
}

void Transform::RotateRightAxis(const float angle)
{
    const float radians = M_PI * (angle / 180.f);
    const Matrix3x3 rotationMatrix{ M3RightRotation(radians) };
    SetOrientation(rotationMatrix.Multiply({ _forward, _right, _up }));
}

void Transform::RotateForwardAxis(const float angle)
{
    const float radians = M_PI * (angle / 180.f);
    const Matrix3x3 rotationMatrix{ M3ForwardRotation(radians) };
    SetOrientation(rotationMatrix.Multiply({ _forward, _right, _up }));
}

void Transform::TranslateForward(const float distance)
{
    Matrix4x4 matrix{
        { 1.f, 0.f, 0.f, _forward.GetElement(0) * distance },
        { 0.f, 1.f, 0.f, _forward.GetElement(1) * distance },
        { 0.f, 0.f, 1.f, _forward.GetElement(2) * distance },
        { 0.f, 0.f, 0.f, 1.f } };

    Vector4 vector(_position, 1.f);
    Vector4 result{ matrix.Multiply(vector) };
    for (int i = 0; i < 3; ++i)
    {
        _position.SetElement(i, result.GetElement(i));
    }
}

void Transform::TranslateRight(const float distance)
{
    Matrix4x4 matrix{
        { 1.f, 0.f, 0.f, _right.GetElement(0) * distance },
        { 0.f, 1.f, 0.f, _right.GetElement(1) * distance },
        { 0.f, 0.f, 1.f, _right.GetElement(2) * distance },
        { 0.f, 0.f, 0.f, 1.f } };

    Vector4 vector(_position, 1.f);
    Vector4 result{ matrix.Multiply(vector) };
    for (int i = 0; i < 3; ++i)
    {
        _position.SetElement(i, result.GetElement(i));
    }
}

void Transform::TranslateUp(const float distance)
{
    Matrix4x4 matrix{
        { 1.f, 0.f, 0.f, _up.GetElement(0) * distance },
        { 0.f, 1.f, 0.f, _up.GetElement(1) * distance },
        { 0.f, 0.f, 1.f, _up.GetElement(2) * distance },
        { 0.f, 0.f, 0.f, 1.f } };

    Vector4 vector(_position, 1.f);
    Vector4 result{ matrix.Multiply(vector) };
    for (int i = 0; i < 3; ++i)
    {
        _position.SetElement(i, result.GetElement(i));
    }
}

void Transform::Translate(const float forward, const float right, const float up)
{
    Matrix4x4 matrix{
        { 1.f, 0.f, 0.f, forward },
        { 0.f, 1.f, 0.f, right },
        { 0.f, 0.f, 1.f, up },
        { 0.f, 0.f, 0.f, 1.f } };

    Vector4 vector(_position, 1.f);
    Vector4 result{ matrix.Multiply(vector) };
    for (int i = 0; i < 3; ++i)
    {
        _position.SetElement(i, result.GetElement(i));
    }
}

void Transform::Translate(const Vector3& vector)
{
    Translate(vector.GetElement(0), vector.GetElement(1), vector.GetElement(2));
}

Matrix4x4 Transform::GetTransformMatrix() const
{
    return {
        { _forward.GetElement(0), _forward.GetElement(1), _forward.GetElement(2), _position.GetElement(0) },
        { _right.GetElement(0), _right.GetElement(1), _right.GetElement(2), _position.GetElement(1) },
        { _up.GetElement(0), _up.GetElement(1), _up.GetElement(2), _position.GetElement(2) },
        { 0.f, 0.f, 0.f, 1.f }
    };
}

const Transform& Object::GetTransformGlobal() const
{
    return _transformGlobal;
}

void Object::SetTransformGlobal(const class Transform& transform)
{
    _transformGlobal = transform;
}

Transform& Object::TransformGlobal()
{
    return _transformGlobal;
}

const Transform& Object::GetTransformLocal() const
{
    return _transformLocal;
}

void Object::SetTransformLocal(const Transform& transform)
{

}

Transform& Object::TransformLocal()
{
    return _transformLocal;
}

const std::vector<std::weak_ptr<Object>>& Object::GetAttachedObjects() const
{
    return _attachedObjects;
}

void Object::AttachToParent(std::weak_ptr<Object> parentPtr, std::weak_ptr<Object> childPtr)
{
    auto child = childPtr.lock();
    auto parent = parentPtr.lock();
    if (!child || !parent)
    {
        return;
    }

    child->SetParent(parentPtr);
    parent->AttachChild(childPtr);
}

const std::weak_ptr<Object> Object::GetParent() const
{
    return _parentPtr;
}

void Object::SetParent(std::weak_ptr<Object> parentPtr)
{
    _parentPtr = parentPtr;
}

void Object::AttachChild(std::weak_ptr<Object> childPtr)
{
    _attachedObjects.push_back(childPtr);
}
