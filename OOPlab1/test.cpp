#include "pch.h"
#include"../Sample-Test1/TritArr.h"
#include"../Sample-Test1/TritArr.cpp"
#include"../Sample-Test1/LogicOp.h"
#include"../Sample-Test1/LogicOp.cpp"
#include"../Sample-Test1/OneTrit.h"
#include"../Sample-Test1/OneTrit.cpp"
#include"CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST(test_onetrit_and, test_name1) {

	ASSERT_EQ(Trit::False, Trit::False&Trit::True);
	ASSERT_EQ(Trit::False, Trit::False&Trit::Unknown);
	ASSERT_EQ(Trit::False, Trit::False&Trit::False);
	ASSERT_EQ(Trit::True, Trit::True&Trit::True);
	ASSERT_EQ(Trit::Unknown, Trit::True&Trit::Unknown);
	ASSERT_EQ(Trit::Unknown, Trit::Unknown&Trit::Unknown);
}

TEST(test_onetrit_or, test_or) {

	ASSERT_EQ(Trit::True, Trit::False | Trit::True);
	ASSERT_EQ(Trit::Unknown, Trit::False | Trit::Unknown);
	ASSERT_EQ(Trit::False, Trit::False | Trit::False);
	ASSERT_EQ(Trit::True, Trit::True | Trit::True);
	ASSERT_EQ(Trit::True, Trit::True | Trit::Unknown);
	ASSERT_EQ(Trit::Unknown, Trit::Unknown | Trit::Unknown);
}

TEST(test_onetrit_not, test_not) {

	ASSERT_EQ(Trit::False, ~Trit::True);
	ASSERT_EQ(Trit::True, ~Trit::False);
	ASSERT_EQ(Trit::Unknown, ~Trit::Unknown);
}

TEST(test_trit_arr, test_name2) {
	TritArr ar1(160);
	TritArr ar2(144);
	ar1.arr[0] = 3;
	ar1.arr[1] = 3;
	ar1.arr[2] = 3;
	ar1.arr[3] = 0;
	ar1.arr[4] = 0;
	ar1.arr[5] = 0;
	ar1.arr[6] = 1;
	ar1.arr[7] = 1;
	ar1.arr[8] = 1;
	ar1.arr[9] = 1;
	ar2.arr[0] = 0;
	ar2.arr[1] = 1;
	ar2.arr[2] = 3;
	ar2.arr[3] = 0;
	ar2.arr[4] = 1;
	ar2.arr[5] = 3;
	ar2.arr[6] = 0;
	ar2.arr[7] = 1;
	ar2.arr[8] = 3;

	TritArr res_and(144);
	res_and.arr[0] = 0;
	res_and.arr[1] = 1;
	res_and.arr[2] = 3;
	res_and.arr[3] = 0;
	res_and.arr[4] = 1;
	res_and.arr[5] = 0;
	res_and.arr[6] = 1;
	res_and.arr[7] = 1;
	res_and.arr[8] = 1;
	
	TritArr hj = ar1 & ar2;

	ASSERT_EQ(res_and.arr, (ar1&ar2).arr);
	ASSERT_EQ(144, (ar1&ar2).capacity());
	TritArr res_or(160);
	res_or.arr[0] = 3;
	res_or.arr[1] = 3;
	res_or.arr[2] = 3;
	res_or.arr[3] = 0;
	res_or.arr[4] = 0;
	res_or.arr[5] = 3;
	res_or.arr[6] = 0;
	res_or.arr[7] = 1;
	res_or.arr[8] = 3;
	res_or.arr[9] = 0;
	ASSERT_EQ(res_or.arr, (ar1|ar2).arr);
	ASSERT_EQ(160, (ar1|ar2).capacity());

	TritArr res_not(160);
	res_not.arr[0] = 1;
	res_not.arr[1] = 1;
	res_not.arr[2] = 1;
	res_not.arr[3] = 0;
	res_not.arr[4] = 0;
	res_not.arr[5] = 0;
	res_not.arr[6] = 3;
	res_not.arr[7] = 3;
	res_not.arr[8] = 3;
	res_not.arr[9] = 3;

	ASSERT_EQ(res_not.arr, (~ar1).arr);
	ASSERT_EQ(160, (~ar1).capacity());
}


TEST(test_read_write_shrink, test_name3) {
	TritArr my_trit(100);
	ASSERT_EQ(0, my_trit.LastUnknown());
	ASSERT_EQ(100, my_trit.capacity());
	
	my_trit.Shrink();
	ASSERT_EQ(0, my_trit.LastUnknown());
	ASSERT_EQ(100, my_trit.capacity());
	
	my_trit[110] = Trit::True;

	ASSERT_EQ(111, my_trit.LastUnknown());
	ASSERT_EQ(111, my_trit.capacity());


	my_trit[110] = Trit::False;

	ASSERT_EQ(111, my_trit.LastUnknown());
	ASSERT_EQ(111, my_trit.capacity());


	my_trit[126] = Trit::True;

	ASSERT_EQ(127, my_trit.LastUnknown());
	ASSERT_EQ(127, my_trit.capacity());
	
	my_trit.Shrink();

	ASSERT_EQ(127, my_trit.LastUnknown());
	ASSERT_EQ(127, my_trit.capacity());
	
	my_trit[126] = Trit::Unknown;
	my_trit.Shrink();

	ASSERT_EQ(111, my_trit.LastUnknown());
	ASSERT_EQ(111, my_trit.capacity());
	
}


TEST(test_equal_trits, test_equal) {
	TritArr trit_one(100);
	trit_one[99] = Trit::True;

	ASSERT_EQ(1, trit_one[99] == Trit::True);
	ASSERT_EQ(0, trit_one[99] == Trit::False);
	ASSERT_EQ(0, trit_one[99] == Trit::Unknown);
}

TEST(test_cardinality, test_name3) {
	TritArr trit(100);
	ASSERT_EQ(0, trit.cardinality(Trit::False));
	ASSERT_EQ(0, trit.cardinality(Trit::True));
	ASSERT_EQ(112, trit.cardinality(Trit::Unknown));

	trit[110] = Trit::True;
	ASSERT_EQ(1, trit.cardinality(Trit::True));
	ASSERT_EQ(0, trit.cardinality(Trit::False));
	ASSERT_EQ(1, trit.cardinality(Trit::Unknown));

	trit[100] = Trit::True;
	ASSERT_EQ(2, trit.cardinality(Trit::True));
	ASSERT_EQ(0, trit.cardinality(Trit::False));
	ASSERT_EQ(1, trit.cardinality(Trit::Unknown));

	trit[110] = Trit::False;
	ASSERT_EQ(1, trit.cardinality(Trit::True));
	ASSERT_EQ(1, trit.cardinality(Trit::False));
	ASSERT_EQ(1, trit.cardinality(Trit::Unknown));
	
	trit[100] = Trit::False;
	ASSERT_EQ(0, trit.cardinality(Trit::True));
	ASSERT_EQ(2, trit.cardinality(Trit::False));
	ASSERT_EQ(1, trit.cardinality(Trit::Unknown));
	
}

TEST(tst_trim, test_name_trim) {
	TritArr trit(100);

	trit[99] = Trit::False;
	trit.Trim(99);
	Trit val = trit[99];
	ASSERT_EQ(0, static_cast<int>(val));

	trit[0] = Trit::False;
	trit[1] = Trit::True;
	trit[99] = Trit::True;
	trit.Trim(0);
	for (int i = 0; i < 100; i++) {
		Trit val = trit[i];
		ASSERT_EQ(0, static_cast<int>(val));
	}
}
