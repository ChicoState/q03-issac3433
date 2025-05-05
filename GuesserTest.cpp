/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}


TEST(GuesserTest, max_tries)
{
	Guesser object("hello");
	object.match("hella");
	object.match("holla");
	object.match("helle");
	ASSERT_FALSE(object.match("hello"));
}

TEST(GuesserTest, wrong_lock)
{
	Guesser object("hello");
	object.match("ijfkbkc");
	ASSERT_FALSE(object.match("hello"));
	ASSERT_EQ(object.remaining(),3);
}

TEST(GuesserTest, remaining_decreases_on_close)
{
	Guesser object("hello");
	object.match("helal");
	ASSERT_EQ(object.remaining(), 2);
}

TEST(GuesserTest, correct_guess_returns_true)
{
	Guesser object("hello");
	ASSERT_TRUE(object.match("hello"));
}

TEST(GuesserTest, long_secret)
{
	 string secretL = "abcdefghijklmnopqrstuvwxyz12345678910";
	 Guesser object(secretL);
	 ASSERT_FALSE(object.match(secretL));
	 ASSERT_EQ(object.remaining(), 3);
	 ASSERT_TRUE(object.match("abcdefghijklmnopqrstuvwxyz123456"));
}

TEST(GuesserTest, short_guess)
{
	Guesser object("country");
	object.match("coun");
	ASSERT_FALSE(object.match("country"));
}

TEST(GuesserTest, remaining_never_goes_negative)
{
    Guesser object("Failure");
    object.match("Failuer");
    object.match("Failuer");
    object.match("Failuer");
    object.match("Failuer"); 
    ASSERT_EQ(object.remaining(), 0);
}

TEST(GuesserTest, case_sensitivty)
{
	Guesser object("Money");
	ASSERT_FALSE(object.match("money"));
	ASSERT_EQ(object.remaining(), 2);
}

TEST(GuesserTest, correct_guess_resets)
{
	Guesser object("pass");
	object.match("pase");
	object.match("pasa");
	ASSERT_EQ(object.remaining(), 1);
	object.match("pass");
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, two_close_then_locks_if_far)
{
	Guesser object("hello");
	object.match("helle");
	object.match("hella");
	ASSERT_EQ(object.remaining(), 1);
	object.match("iiiii");
	ASSERT_FALSE(object.match("hello"));
}

TEST(GuesserTest, longer_than_secret_guess)
{
	Guesser object("guess");
	object.match("guessisclose");
	ASSERT_FALSE(object.match("guess"));
}