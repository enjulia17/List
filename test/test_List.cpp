#include "List.h"

#include <gtest.h>


TEST(ListElem, can_create_element_in_list)
{
	ASSERT_NO_THROW(TListElem<int> e(9));
}

TEST(ListElem, can_set_data_element_in_list)
{
	TListElem<int> e(9);
	ASSERT_NO_THROW(e.SetData(10));
}

TEST(ListElem, can_get_data_of_element_in_list)
{
	TListElem<int> e(5);
	EXPECT_EQ(e.GetData(), 5);
}

TEST(List, can_create_list)
{
	ASSERT_NO_THROW(TList<int>());
}

TEST(List, can_insert_first_element)
{
	TList<int> f;
	ASSERT_NO_THROW(f.InsFirst(5));
}

TEST(List, can_insert_last_element)
{
	TList<int> l;
	ASSERT_NO_THROW(l.InsLast(5));
}

TEST(List, can_get_first_element)
{

	TList<int> f;
	int o = 9;
	int p = 3;
	f.InsFirst(o);
	f.InsLast(p);
	EXPECT_EQ(9, f.GetFirst()->GetData());
}

TEST(List, can_get_last_element)
{

	TList<int> l;
	int o = 9;
	int p = 3;
	l.InsFirst(o);
	l.InsLast(p);
	EXPECT_EQ(3, l.GetLast()->GetData());
}

TEST(List, cannot_get_element_from_empty_list)
{
	TList<int> e;
	ASSERT_ANY_THROW(e.GetLast());
}

TEST(List, cannot_delete_element_from_empty_list)
{
	TList<int> e;
	ASSERT_ANY_THROW(e.DelLast());
}

