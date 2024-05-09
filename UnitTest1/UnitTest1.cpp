#include "pch.h"
#include "CppUnitTest.h"
#include "../LB_12.11.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

        TEST_METHOD(TestRemoveTicketRequest)
        {
            TicketRequest* root = nullptr;

            TicketRequest* request1 = new TicketRequest;
            request1->destination = "New York";
            request1->flightNumber = 123;
            request1->passengerName = "John Doe";
            request1->departureDate = "2024-05-20";
            request1->left = nullptr;
            request1->right = nullptr;
            addTicketRequest(root, request1);

            TicketRequest* request2 = new TicketRequest;
            request2->destination = "London";
            request2->flightNumber = 456;
            request2->passengerName = "Alice Smith";
            request2->departureDate = "2024-05-25";
            request2->left = nullptr;
            request2->right = nullptr;
            addTicketRequest(root, request2);

            root = removeTicketRequest(root, 123, "2024-05-20");

            Assert::IsNull(root->left);
            Assert::AreEqual(root->destination, std::string("London"));
            Assert::AreEqual(root->flightNumber, 456);
            Assert::AreEqual(root->passengerName, std::string("Alice Smith"));
            Assert::AreEqual(root->departureDate, std::string("2024-05-25"));

            deleteTree(root);
        }
	};
}
