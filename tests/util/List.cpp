// Copyright (C) 2014, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#include "tests/framework/Framework.h"
#include "tests/util/Foo.h"
#include "anki/util/List.h"

ANKI_TEST(Util, List)
{
	HeapAllocator<U8> alloc(allocAligned, nullptr);

	// Simple
	{
		List<Foo> a;
		Error err = ErrorCode::NONE;

		err = a.emplaceBack(alloc, 10);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);
		err = a.emplaceBack(alloc, 11);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);

		U sum = 0;

		err = a.iterateForward([&](const Foo& f) -> Error
		{
			sum += f.x;
			return ErrorCode::NONE;
		});

		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);
		ANKI_TEST_EXPECT_EQ(sum, 21);

		a.destroy(alloc);
	}

	// Sort
	{
		List<I> a;
		Error err = ErrorCode::NONE;

		err = a.emplaceBack(alloc, 10);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);
		err = a.emplaceBack(alloc, 9);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);
		err = a.emplaceBack(alloc, 11);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);
		err = a.emplaceBack(alloc, 2);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);

		a.sort();

		Array<I, 4> arr = {{2, 9, 10, 11}};
		U u = 0;

		err = a.iterateForward([&](const I& i) -> Error
		{
			if(arr[u++] == i)
			{
				return ErrorCode::NONE;
			}
			else
			{
				return ErrorCode::UNKNOWN;
			}
		});

		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);

		a.sort([](I& a, I& b) -> Bool
		{
			return a > b;
		});

		Array<I, 4> arr2 = {{11, 10, 9, 2}};
		u = 0;

		err = a.iterateForward([&](const I& i) -> Error
		{
			if(arr2[u++] == i)
			{
				return ErrorCode::NONE;
			}
			else
			{
				return ErrorCode::UNKNOWN;
			}
		});

		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);

		a.destroy(alloc);
	}

	// Iterate
	{
		List<I> a;
		Error err = ErrorCode::NONE;

		err = a.emplaceBack(alloc, 10);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);
		err = a.emplaceBack(alloc, 9);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);
		err = a.emplaceBack(alloc, 11);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);
		err = a.emplaceBack(alloc, 2);
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);

		Array<I, 4> arr = {{10, 9, 11, 2}};
		U count = 0;
		
		// Forward
		List<I>::ConstIterator it = a.getBegin();
		for(; it != a.getEnd() && !err; ++it)
		{
			if(*it != arr[count++])
			{
				err = ErrorCode::UNKNOWN;
			}
		}
		
		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);

		// Backwards
		--it;
		for(; it != a.getBegin() && !err; --it)
		{
			if(*it != arr[--count])
			{
				err = ErrorCode::UNKNOWN;
			}
		}

		ANKI_TEST_EXPECT_EQ(err, ErrorCode::NONE);

		a.destroy(alloc);
	}

	// Erase
	{
		List<I> a;

		ANKI_TEST_EXPECT_EQ(a.emplaceBack(alloc, 10), ErrorCode::NONE);

		a.erase(alloc, a.getBegin());
		ANKI_TEST_EXPECT_EQ(a.isEmpty(), true);

		ANKI_TEST_EXPECT_EQ(a.emplaceBack(alloc, 10), ErrorCode::NONE);
		ANKI_TEST_EXPECT_EQ(a.emplaceBack(alloc, 20), ErrorCode::NONE);

		a.erase(alloc, a.getBegin() + 1);
		ANKI_TEST_EXPECT_EQ(10, *a.getBegin());

		ANKI_TEST_EXPECT_EQ(a.emplaceFront(alloc, 5), ErrorCode::NONE);
		ANKI_TEST_EXPECT_EQ(a.emplaceBack(alloc, 30), ErrorCode::NONE);

		ANKI_TEST_EXPECT_EQ(5, *(a.getBegin()));
		ANKI_TEST_EXPECT_EQ(10, *(a.getEnd() - 2));
		ANKI_TEST_EXPECT_EQ(30, *(a.getEnd() - 1));
		
		a.erase(alloc, a.getEnd() - 2);
		ANKI_TEST_EXPECT_EQ(5, *(a.getBegin()));
		ANKI_TEST_EXPECT_EQ(30, *(a.getEnd() - 1));

		a.erase(alloc, a.getBegin());
		a.erase(alloc, a.getBegin());
	}
}

