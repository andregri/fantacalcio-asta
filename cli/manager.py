import argparse
import logging, sys

# import my modules
import commands


# init logger
logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='Asta Fantacalcio Manager')
    subparsers = parser.add_subparsers(help='sub-command help')

    # create the parser for the "add" command
    parser_add = subparsers.add_parser('add', help='add a player to a roster')
    parser_add.add_argument('player', type=str, help='player name')
    parser_add.add_argument('team', type=str, help='fantasy team name')
    parser_add.add_argument('cost', type=int, help='cost payed by the fantasy team to buy the player')
    parser_add.set_defaults(func=commands.add_player)

    # create the parser for the "delete" command
    parser_delete = subparsers.add_parser('delete', help='delete a player transfer from a roster')
    parser_delete.add_argument('player', type=str, help='player name')
    parser_delete.set_defaults(func=commands.delete_transfer)

    # crete the parser for the "estimate" command
    parser_estimate = subparsers.add_parser('estimate', help='estimate the maximum offer by each team')
    parser_estimate.add_argument('player', type=str, help='player name')
    parser_estimate.set_defaults(func=commands.estimate_offer)


    args = parser.parse_args()
    args.func(**args.__dict__)