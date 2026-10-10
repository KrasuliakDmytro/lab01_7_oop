#include "pch.h"
#include "CppUnitTest.h"
#include "../lr1_7/Bill.h"
#include "../lr1_7/Time.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

        TEST_METHOD(TestBillInit)
        {
            Bill bill;
            Time start(10, 0, 0);
            Time end(10, 2, 0);

            bill.Init(
                "Іваненко",
                "+380991234567",
                5.0,
                0.0,
                start,
                end
            );

            Assert::AreEqual(string("Іваненко"), bill.GetSurname());
            Assert::AreEqual(string("+380991234567"), bill.GetPhoneNumber());
            Assert::AreEqual(5.0, bill.GetTariff(), 0.001);
            Assert::AreEqual(0.0, bill.GetDiscount(), 0.001);
            Assert::AreEqual(10.0, bill.GetAmount(), 0.001);
        }

        TEST_METHOD(TestBillCopyConstructor)
        {
            Time start(10, 0, 0);
            Time end(10, 2, 0);

            Bill b1(
                "Іваненко",
                "+380991234567",
                5.0,
                0.0,
                start,
                end
            );

            Bill b2(b1);

            Assert::AreEqual(b1.GetSurname(), b2.GetSurname());
            Assert::AreEqual(b1.GetPhoneNumber(), b2.GetPhoneNumber());
            Assert::AreEqual(b1.GetTariff(), b2.GetTariff(), 0.001);
            Assert::AreEqual(b1.GetAmount(), b2.GetAmount(), 0.001);
        }

        TEST_METHOD(TestBillCalculateAmount)
        {
            Time start(10, 0, 0);
            Time end(10, 2, 0);

            Bill bill(
                "Іваненко",
                "+380991234567",
                5.0,
                0.0,
                start,
                end
            );

            Assert::AreEqual(10.0, bill.GetAmount(), 0.001);
        }

        TEST_METHOD(TestBillDiscount)
        {
            Time start(10, 0, 0);
            Time end(10, 2, 0);

            Bill bill(
                "Петренко",
                "+380991234567",
                10.0,
                20.0,
                start,
                end
            );

            Assert::AreEqual(16.0, bill.GetAmount(), 0.001);
        }

        TEST_METHOD(TestBillPartialMinute)
        {
            Time start(10, 0, 0);
            Time end(10, 1, 1);

            Bill bill(
                "Шевченко",
                "+380991234567",
                4.0,
                0.0,
                start,
                end
            );

            Assert::AreEqual(8.0, bill.GetAmount(), 0.001);
        }

        TEST_METHOD(TestBillAcrossMidnight)
        {
            Time start(23, 59, 0);
            Time end(0, 1, 0);

            Bill bill(
                "Коваленко",
                "+380991234567",
                3.0,
                0.0,
                start,
                end
            );

            Assert::AreEqual(6.0, bill.GetAmount(), 0.001);
        }

        TEST_METHOD(TestBillSetTariff)
        {
            Time start(10, 0, 0);
            Time end(10, 2, 0);

            Bill bill(
                "Іваненко",
                "+380991234567",
                5.0,
                0.0,
                start,
                end
            );

            bill.SetTariff(7.0);

            Assert::AreEqual(14.0, bill.GetAmount(), 0.001);
        }

        TEST_METHOD(TestBillSetDiscount)
        {
            Time start(10, 0, 0);
            Time end(10, 2, 0);

            Bill bill(
                "Іваненко",
                "+380991234567",
                10.0,
                0.0,
                start,
                end
            );

            bill.SetDiscount(20.0);

            Assert::AreEqual(16.0, bill.GetAmount(), 0.001);
        }

        TEST_METHOD(TestBillToString)
        {
            Time start(10, 0, 0);
            Time end(10, 2, 0);

            Bill bill(
                "Іваненко",
                "+380991234567",
                5.0,
                0.0,
                start,
                end
            );

            Assert::IsTrue(bill.toString() == "10.00 грн");
        }
	};
}
