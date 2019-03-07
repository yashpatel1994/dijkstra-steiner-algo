#include <boost/test/unit_test.hpp>
#include "../src/TerminalSubset.h"
#include "fixtures/general_fixtures.h"



struct TerminalSubsetFixture : public ThreeTerminalsFixture
{};

BOOST_FIXTURE_TEST_CASE(TestTerminalSubset_get_index, TerminalSubsetFixture)
{
	BOOST_TEST(0 == empty.get_index());
	BOOST_TEST(7 == full.get_index());
	BOOST_TEST(1 == singleton_0.get_index());
	BOOST_TEST(2 == singleton_1.get_index());
	BOOST_TEST(4 == singleton_2.get_index());
}

BOOST_FIXTURE_TEST_CASE(TestTerminalSubset_contains, TerminalSubsetFixture)
{
	BOOST_TEST(not empty.contains(full));
	BOOST_TEST(not empty.contains(singleton_0));
	BOOST_TEST(not empty.contains(singleton_1));
	BOOST_TEST(not empty.contains(singleton_2));
	BOOST_TEST(empty.contains(empty));
	BOOST_TEST(singleton_0.contains(singleton_0));
	BOOST_TEST(singleton_1.contains(singleton_1));
	BOOST_TEST(singleton_2.contains(singleton_2));
	BOOST_TEST(not singleton_1.contains(full));
	BOOST_TEST(full.contains(singleton_0));
	BOOST_TEST(full.contains(singleton_1));
	BOOST_TEST(full.contains(singleton_2));
}

BOOST_FIXTURE_TEST_CASE(TestTerminalSubset_plus, TerminalSubsetFixture)
{
	BOOST_CHECK(singleton_0 == TerminalSubset(empty).plus(singleton_0));
	BOOST_CHECK(full == TerminalSubset(full).plus(singleton_0));
	BOOST_CHECK(full == TerminalSubset(singleton_0).plus(full));
}

BOOST_FIXTURE_TEST_CASE(TestTerminalSubset_create_nonempty_subsets, TerminalSubsetFixture)
{
	BOOST_TEST(0 == empty.create_nonempty_subsets().size());
	auto const debug = full.create_nonempty_subsets();
	BOOST_TEST(pow2(terminals.size()) - 1 == debug.size());
}

BOOST_FIXTURE_TEST_CASE(TestTerminalSubset_empty, TerminalSubsetFixture)
{
	BOOST_TEST(empty.empty());
	BOOST_TEST(not singleton_0.empty());
	BOOST_TEST(not singleton_1.empty());
	BOOST_TEST(not singleton_2.empty());
	BOOST_TEST(not full.empty());
}