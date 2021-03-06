#include "stdafx.h"
#include "../MultiGumballMachine/MultiGumBallMachineWithState.h"
#include "../MultiGumballMachine/NaiveGumBallMachine.h"

template <typename GumballMachineType>
void AssertState(const GumballMachineType& machine, const std::string& state, size_t gumballs, size_t coins)
{
	boost::format outputFormat = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
Number of coins: %4%
)")
		% gumballs % (gumballs == 1 ? "" : "s")
		% state
		% coins;

	BOOST_CHECK_EQUAL(machine.ToString(), outputFormat.str());
};

BOOST_AUTO_TEST_SUITE(MultiGumBallMachine)

	BOOST_AUTO_TEST_SUITE(receive_gum_balls_at_amount_of_0)
		boost::test_tools::output_test_stream output;

		struct CMultiGumBallMachine_
		{
			CMultiGumBallMachine_()
				: machine(0, output)
			{
			}
			with_state::CMultiGumballMachine machine;
		};
		BOOST_FIXTURE_TEST_CASE(can_be_refill, CMultiGumBallMachine_)
		{
			machine.Refill(10);
			BOOST_CHECK(output.is_equal("Added 10 gum balls\n"));
			AssertState(machine, "waiting for coin", 10, 0);
		}
		BOOST_FIXTURE_TEST_SUITE(does_not_change_state_when, CMultiGumBallMachine_)

			BOOST_AUTO_TEST_CASE(insert_coin)
			{
				machine.InsertCoin();
				BOOST_CHECK(output.is_equal("You can't insert a coin, the machine is sold out\n"));
				AssertState(machine, "sold out", 0, 0);
			}

			BOOST_AUTO_TEST_CASE(eject_coin)
			{
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You can't eject, you haven't inserted a coin yet\n"));
				AssertState(machine, "sold out", 0, 0);
			}

			BOOST_AUTO_TEST_CASE(turn_crank)
			{
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You turned but there's no gumballs\nNo gumball dispensed\n"));
				AssertState(machine, "sold out", 0, 0);
			}

			BOOST_AUTO_TEST_CASE(refill_on_0)
			{
				machine.Refill(0);
				BOOST_CHECK(output.is_equal("Added 0 gum balls\n"));
				AssertState(machine, "sold out", 0, 0);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(receive_gum_balls_at_amount_greater_than_0)
		boost::test_tools::output_test_stream output;
		struct CMultiGumBallMachine_
		{
			CMultiGumBallMachine_()
				: machine(13, output)
			{
			}
			with_state::CMultiGumballMachine machine;
		};

		BOOST_FIXTURE_TEST_SUITE(is_at_NoCoin_state, CMultiGumBallMachine_)

			BOOST_AUTO_TEST_CASE(changes_state_when_insertion_coin)
			{
				machine.InsertCoin();
				BOOST_CHECK(output.is_equal("You inserted a coin\n"));
				AssertState(machine, "waiting for turn of crank", 13, 1);
			}

			BOOST_AUTO_TEST_CASE(do_not_change_state_when_refill_on_0)
			{
				machine.Refill(0);
				BOOST_CHECK(output.is_equal("Added 0 gum balls\n"));
				AssertState(machine, "waiting for coin", 13, 0);
			}

			BOOST_AUTO_TEST_CASE(do_not_change_state_when_eject_coin)
			{
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You haven't inserted a coin\n"));
				AssertState(machine, "waiting for coin", 13, 0);
			}

			BOOST_AUTO_TEST_CASE(do_not_change_state_when_turn_crank)
			{
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You turned but there's no coin\nYou need to pay first\n"));
				AssertState(machine, "waiting for coin", 13, 0);
			}

			BOOST_AUTO_TEST_CASE(can_be_refill)
			{
				machine.Refill(3);
				BOOST_CHECK(output.is_equal("Added 3 gum balls\n"));
				AssertState(machine, "waiting for coin", 16, 0);
			}

			BOOST_AUTO_TEST_CASE(can_be_inserted_no_more_than_5_coins)
			{
				for (size_t i = 0; i < 6; ++i)
				{
					machine.InsertCoin();
				}
				BOOST_CHECK(!output.is_equal("You inserted a coin\nYou inserted a coin\nYou inserted a coin\nYou inserted a coin\nYou inserted a coin\nYou inserted a coin\n"));

				AssertState(machine, "waiting for turn of crank", 13, 5);
			}

		BOOST_AUTO_TEST_SUITE_END()

		struct CMultiGumBallMachineHasCoin_
		{
			CMultiGumBallMachineHasCoin_()
				: machine(1, output)
			{
				machine.InsertCoin();
			}
			with_state::CMultiGumballMachine machine;
		};

		BOOST_FIXTURE_TEST_SUITE(is_at_HasCoin_state, CMultiGumBallMachineHasCoin_)

			BOOST_AUTO_TEST_CASE(changes_state_when_insertion_coin)
			{
				machine.InsertCoin();
				BOOST_CHECK(output.is_equal("You inserted a coin\nYou inserted a coin\n"));
				AssertState(machine, "waiting for turn of crank", 1, 2);
			}

			BOOST_AUTO_TEST_CASE(do_not_change_state_when_refill_on_0)
			{
				machine.Refill(0);
				BOOST_CHECK(output.is_equal("You inserted a coin\nAdded 0 gum balls\n"));
				AssertState(machine, "waiting for turn of crank", 1, 1);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_eject_coin)
			{
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You inserted a coin\nCoin returned\n"));
				AssertState(machine, "waiting for coin", 1, 0);
			}

			BOOST_AUTO_TEST_CASE(changes_state_and_return_all_coins)
			{
				machine.InsertCoin();
				AssertState(machine, "waiting for turn of crank", 1, 2);
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You inserted a coin\nYou inserted a coin\nCoin returned\nCoin returned\n"));
				AssertState(machine, "waiting for coin", 1, 0);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_get_last_gum_ball_and_no_coins)
			{
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You inserted a coin\nYou turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n"));
				AssertState(machine, "sold out", 0, 0);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_get_last_gum_ball_and_has_coins)
			{
				machine.InsertCoin();
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You inserted a coin\nYou inserted a coin\nYou turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n"));
				AssertState(machine, "waiting for turn of crank", 0, 1);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_get_gum_ball_and_no_coins)
			{
				machine.Refill(3);
				AssertState(machine, "waiting for turn of crank", 4, 1);
				machine.TurnCrank();
				AssertState(machine, "waiting for coin", 3, 0);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(NaiveMultiGumBallMachine)

	BOOST_AUTO_TEST_SUITE(receive_gum_balls_at_amount_of_0)
		boost::test_tools::output_test_stream output;

		struct CMultiGumBallMachine_
		{
			CMultiGumBallMachine_()
				: machine(0, output)
			{
			}
			naive::CMultiGumballMachine machine;
		};
		BOOST_FIXTURE_TEST_SUITE(does_not_change_state_when, CMultiGumBallMachine_)

			BOOST_AUTO_TEST_CASE(insert_coin)
			{
				machine.InsertCoin();
				BOOST_CHECK(output.is_equal("You can't insert a coin, the machine is sold out\n"));
				AssertState(machine, "sold out", 0, 0);
			}

			BOOST_AUTO_TEST_CASE(eject_coin)
			{
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You can't eject, you haven't inserted a coin yet\n"));
				AssertState(machine, "sold out", 0, 0);
			}

			BOOST_AUTO_TEST_CASE(turn_crank)
			{
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You turned but there's no gumballs\n"));
				AssertState(machine, "sold out", 0, 0);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(receive_gum_balls_at_amount_greater_than_0)
		boost::test_tools::output_test_stream output;
		struct CMultiGumBallMachine_
		{
			CMultiGumBallMachine_()
				: machine(13, output)
			{
			}
			naive::CMultiGumballMachine machine;
		};

		BOOST_FIXTURE_TEST_SUITE(is_at_NoCoin_state, CMultiGumBallMachine_)

			BOOST_AUTO_TEST_CASE(changes_state_when_insertion_coin)
			{
				machine.InsertCoin();
				BOOST_CHECK(output.is_equal("You inserted a coin\n"));
				AssertState(machine, "waiting for turn of crank", 13, 1);
			}

			BOOST_AUTO_TEST_CASE(do_not_change_state_when_eject_coin)
			{
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You haven't inserted a coin\n"));
				AssertState(machine, "waiting for coin", 13, 0);
			}

			BOOST_AUTO_TEST_CASE(do_not_change_state_when_turn_crank)
			{
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You turned but there's no coin\n"));
				AssertState(machine, "waiting for coin", 13, 0);
			}

			BOOST_AUTO_TEST_CASE(can_be_inserted_no_more_than_5_coins)
			{
				for (size_t i = 0; i < 6; ++i)
				{
					machine.InsertCoin();
				}
				BOOST_CHECK(!output.is_equal("You inserted a coin\nYou inserted a coin\nYou inserted a coin\nYou inserted a coin\nYou inserted a coin\nYou inserted a coin\n"));

				AssertState(machine, "waiting for turn of crank", 13, 5);
			}

		BOOST_AUTO_TEST_SUITE_END()

		struct CMultiGumBallMachineHasCoin_
		{
			CMultiGumBallMachineHasCoin_()
				: machine(1, output)
			{
				machine.InsertCoin();
			}
			naive::CMultiGumballMachine machine;
		};

		BOOST_FIXTURE_TEST_SUITE(is_at_HasCoin_state, CMultiGumBallMachineHasCoin_)

			BOOST_AUTO_TEST_CASE(changes_state_when_insertion_coin)
			{
				machine.InsertCoin();
				BOOST_CHECK(output.is_equal("You inserted a coin\nYou inserted a coin\n"));
				AssertState(machine, "waiting for turn of crank", 1, 2);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_eject_coin)
			{
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You inserted a coin\nCoin returned\n"));
				AssertState(machine, "waiting for coin", 1, 0);
			}

			BOOST_AUTO_TEST_CASE(changes_state_and_return_all_coins)
			{
				machine.InsertCoin();
				AssertState(machine, "waiting for turn of crank", 1, 2);
				machine.EjectCoin();
				BOOST_CHECK(output.is_equal("You inserted a coin\nYou inserted a coin\nCoin returned\nCoin returned\n"));
				AssertState(machine, "waiting for coin", 1, 0);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_get_last_gum_ball_and_no_coins)
			{
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You inserted a coin\nYou turned...\nA gumball comes rolling out the slot\nOops, out of gumballs\n"));
				AssertState(machine, "sold out", 0, 0);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_get_last_gum_ball_and_has_coins)
			{
				machine.InsertCoin();
				machine.TurnCrank();
				BOOST_CHECK(output.is_equal("You inserted a coin\nYou inserted a coin\nYou turned...\nA gumball comes rolling out the slot\nOops, out of gumballs\n"));
				AssertState(machine, "waiting for turn of crank", 0, 1);
			}

			BOOST_AUTO_TEST_CASE(changes_state_when_get_gum_ball_and_no_coins)
			{
				naive::CMultiGumballMachine naiveMachine(4, output);
				naiveMachine.InsertCoin();
				AssertState(naiveMachine, "waiting for turn of crank", 4, 1);
				naiveMachine.TurnCrank();
				AssertState(naiveMachine, "waiting for coin", 3, 0);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
