#pragma once
namespace YoungEngine {
	class Vector3 {
	public:
		float x;
		float y;
		float z;
	private:
		float padding;
	public:
		Vector3();
		Vector3(float px, float py, float pz);
		void invert();
		float magnitude()const;
		float squareMagnitude()const;
		void normalize();
		/// <summary>
		/// set all components to zero
		/// </summary>
		void clear();
		Vector3 operator*(float val) const;
		friend Vector3 operator*(float val, const Vector3& v);
		Vector3& operator*=(float val);
		Vector3 operator+(const Vector3& other) const;
		Vector3& operator+=(const Vector3& other);
		Vector3 operator-(const Vector3& other) const;
		Vector3& operator-=(const Vector3& other);
		Vector3& operator-();
		void addScaledVector(const Vector3& other,float factor);
		Vector3 componentProduct(const Vector3& other)const;
		void componentProductUpdate(const Vector3& other);
		float dot(const Vector3& other) const;
		float operator*(const Vector3& other)const;
		Vector3 cross(const Vector3& other) const;
	};
};