#include "CppUnitTest.h"
#include "../Battle City/Vectors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define EPSILON 0.1

bool AreSame(double a, double b)
{
	return fabs(a - b) < EPSILON;
}

namespace UnitTesting
{
	TEST_CLASS(VectorTesting)
	{
	public:
		
		TEST_METHOD(testPlus)
		{
			Vector2 vector1(1., 2.);
			Vector2 vector2(3., 5.);
			Vector2 result = vector1 + vector2;

			Assert::AreEqual(true, AreSame(result.x, 4.));
		}

		TEST_METHOD(testMinus)
		{
			Vector2 vector1(1., 2.);
			Vector2 vector2(3., 5.);
			Vector2 result = vector1 - vector2;
			Assert::AreEqual(true, AreSame(result.x, -2.));
		}

		TEST_METHOD(testMultiply)
		{
			Vector2 vector1(1., 2.);
			double x = 5;
			Vector2 result = vector1 * x;
			Assert::AreEqual(true, AreSame(result.y, 10.));
		}

		TEST_METHOD(testEqual)
		{
			Vector2 vector1(1., 2.);
			Vector2 vector2(1., 2.);
			bool result = vector1 == vector2;
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(testMagnitude)
		{
			Vector2 vector1(3., 4.);
			double result = vector1.Magnitude();
			Assert::AreEqual(true, AreSame(result, 5.));
		}

		TEST_METHOD(testNormalize)
		{
			Vector2 vector1(3., 4.);
			Vector2 result = vector1.Normalize();
			Assert::AreEqual(true, AreSame(result.y, 0.8));
		}

		TEST_METHOD(testAngle)
		{
			Vector2 vector1(1., 0.);
			Vector2 vector2(0., 1.);
			double angle = vector1.VectorAngle(vector2) * Rad2Deg;
			Assert::AreEqual(true, AreSame(angle, 90));
		}

		TEST_METHOD(testString)
		{
			Vector2 vector1(56.65, -39.31);
			Assert::AreEqual("56 -39", vector1.toString().c_str());
		}
	};
}
