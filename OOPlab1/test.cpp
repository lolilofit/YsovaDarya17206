#include "pch.h"
#include"../test_trit/LogicOp.h"
#include"../test_trit/LogicOp.cpp"
#include"../test_trit/OneTrit.h"
#include"../test_trit/OneTrit.cpp"
#include"../test_trit/TritArr.h"
#include"../test_trit/TritArr.cpp"

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

TEST(test_trits_and, test_name2) {
	TritSet ar1(6);
	TritSet ar2(16);
	
	ar1[0] = Trit::True;
	ar1[1] = Trit::Unknown;
	ar1[2] = Trit::Unknown;
	ar1[3] = Trit::False;
	ar1[4] = Trit::False;
	ar1[5] = Trit::False;

	ar2[0] = Trit::False;
	ar2[1] = Trit::False;
	ar2[2] = Trit::Unknown;
	ar2[3] = Trit::False;
	ar2[4] = Trit::Unknown;
	ar2[5] = Trit::True;
	
	TritSet res(6);
	res[0] = Trit::False;
	res[1] = Trit::False;
	res[2] = Trit::Unknown;
	res[3] = Trit::False;
	res[4] = Trit::False;
	res[5] = Trit::False;

	for (int i = 0; i < (ar1&ar2).capacity(); i++)
		ASSERT_EQ(res.read(i), (ar1&ar2).read(i));

	ASSERT_EQ(6, (ar1&ar2).capacity());
}


TEST(test_trits_or, test_name_or) {
	TritSet ar1(6);
	TritSet ar2(16);

	ar1[0] = Trit::True;
	ar1[1] = Trit::Unknown;
	ar1[2] = Trit::Unknown;
	ar1[3] = Trit::False;
	ar1[4] = Trit::False;
	ar1[5] = Trit::False;

	ar2[0] = Trit::False;
	ar2[1] = Trit::False;
	ar2[2] = Trit::Unknown;
	ar2[3] = Trit::False;
	ar2[4] = Trit::Unknown;
	ar2[5] = Trit::True;
	ar2[6] = Trit::True;

	TritSet res(16);
	res[0] = Trit::True;
	res[1] = Trit::Unknown;
	res[2] = Trit::Unknown;
	res[3] = Trit::False;
	res[4] = Trit::Unknown;
	res[5] = Trit::True;
	res[6] = Trit::True;

	for (int i = 0; i < (ar1|ar2).capacity(); i++)
		ASSERT_EQ(res.read(i), (ar1|ar2).read(i));

	ASSERT_EQ(16, (ar1|ar2).capacity());
}


TEST(test_trits_not, test_name_trits) {
	TritSet ar1(48);

	ar1[0] = Trit::True;
	ar1[1] = Trit::Unknown;
	ar1[2] = Trit::False;
	
	TritSet res(48);
	res[0] = Trit::False;
	res[1] = Trit::Unknown;
	res[2] = Trit::True;
	
	for (int i = 0; i < (~(ar1)).capacity(); i++)
		ASSERT_EQ(res.read(i), (~(ar1)).read(i));

	ASSERT_EQ(48, (~(ar1)).capacity());
}

TEST(test_shrink_operators, test_name3) {
	TritSet my_trit(100);
	ASSERT_EQ(0, my_trit.lenght());
	ASSERT_EQ(100, my_trit.capacity());

	my_trit.shrink();
	ASSERT_EQ(0, my_trit.lenght());
	ASSERT_EQ(100, my_trit.capacity());

	my_trit[110] = Trit::True;

	ASSERT_EQ(111, my_trit.lenght());
	ASSERT_EQ(111, my_trit.capacity());


	my_trit[110] = Trit::False;

	ASSERT_EQ(111, my_trit.lenght());
	ASSERT_EQ(111, my_trit.capacity());


	my_trit[126] = Trit::True;

	ASSERT_EQ(127, my_trit.lenght());
	ASSERT_EQ(127, my_trit.capacity());

	my_trit.shrink();

	ASSERT_EQ(127, my_trit.lenght());
	ASSERT_EQ(127, my_trit.capacity());

	my_trit[126] = Trit::Unknown;
	my_trit.shrink();

	ASSERT_EQ(111, my_trit.lenght());
	ASSERT_EQ(111, my_trit.capacity());

}


TEST(test_equal_trits, test_equal) {
	TritSet trit_one(100);
	trit_one[99] = Trit::True;

	ASSERT_EQ(1, trit_one[99] == Trit::True);
	ASSERT_EQ(0, trit_one[99] == Trit::False);
	ASSERT_EQ(0, trit_one[99] == Trit::Unknown);

	trit_one[99] = Trit::False;

	ASSERT_EQ(0, trit_one[99] == Trit::True);
	ASSERT_EQ(1, trit_one[99] == Trit::False);
	ASSERT_EQ(0, trit_one[99] == Trit::Unknown);

	trit_one[99] = Trit::Unknown;

	ASSERT_EQ(0, trit_one[99] == Trit::True);
	ASSERT_EQ(0, trit_one[99] == Trit::False);
	ASSERT_EQ(1, trit_one[99] == Trit::Unknown);
}

TEST(test_cardinality, test_name3) {
	TritSet trit(100);
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
	TritSet trit(100);

	trit[99] = Trit::False;
	trit.trim(99);
	Trit val = trit[99];
	ASSERT_EQ(0, static_cast<int>(val));

	trit[0] = Trit::False;
	trit[1] = Trit::True;
	trit[99] = Trit::True;
	trit.trim(0);
	for (int i = 0; i < 100; i++) {
		Trit val = trit[i];
		ASSERT_EQ(0, static_cast<int>(val));
	}
}

TEST(test_unordered_map, test_name_map) {
	TritSet trit(100);
	trit[110] = Trit::True;
    
	std::unordered_map< Trit, int, std::hash<Trit> > result = trit.cardinality();
	ASSERT_EQ(1, result[Trit::True]);
	ASSERT_EQ(1, result[Trit::Unknown]);
	ASSERT_EQ(0, result[Trit::False]);

	trit[100] = Trit::True;

	result = trit.cardinality();
	ASSERT_EQ(2, result[Trit::True]);
	ASSERT_EQ(1, result[Trit::Unknown]);
	ASSERT_EQ(0, result[Trit::False]);

	trit[110] = Trit::False;

	result = trit.cardinality();
	ASSERT_EQ(1, result[Trit::True]);
	ASSERT_EQ(1, result[Trit::Unknown]);
	ASSERT_EQ(1, result[Trit::False]);
	
	trit[100] = Trit::False;

	result = trit.cardinality();
	ASSERT_EQ(0, result[Trit::True]);
	ASSERT_EQ(1, result[Trit::Unknown]);
	ASSERT_EQ(2, result[Trit::False]);
}

TEST(test_set_trit, test_name_set) {
	TritSet trit(100);

	trit.set_trir(99, Trit::True);
	Trit res = trit[99];
	ASSERT_EQ(res, Trit::True);

	trit.set_trir(90, Trit::False);
	res = trit[90];
	ASSERT_EQ(res, Trit::False);

	trit.set_trir(56, Trit::Unknown);
	res = trit[56];
	ASSERT_EQ(res, Trit::Unknown);

}

TEST(test_read_trit, test_name_read) {
	TritSet trit(100);
	trit[99] = Trit::True;
	ASSERT_EQ(3 , trit.read(99));

	trit[90] = Trit::False;
	ASSERT_EQ(1, trit.read(90));

	trit[89] = Trit::Unknown;
	ASSERT_EQ(0, trit.read(89));
}

TEST(equality_cast_operator, test_name_equality) {
	TritSet trit(100);

	trit[99] = Trit::True;
	ASSERT_EQ(Trit::True, trit[99]);

	trit[99] = Trit::False;
	ASSERT_EQ(Trit::False, trit[99]);

	trit[99] = Trit::Unknown;
	ASSERT_EQ(Trit::Unknown, trit[99]);
}
