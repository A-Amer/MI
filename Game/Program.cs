using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ChessDotNet;

namespace Gm
{
    class Program
    {
        private static void DrawBoard(ChessGame game)
        {
            //Console.Clear();

            for (int j = 8; j >= 1; j--)
            {
                Console.WriteLine();
                Console.WriteLine(" ---------------------------------");
                Console.Write(j);
                for (File i = File.A; i <= File.H; i++)
                {
                    string str;
                    Piece PieceType = game.GetPieceAt(i, j);
                    if (PieceType == null)
                    {
                        str = "| " + "  ";
                    }
                    else
                    {
                        str = "| " + PieceType.GetFenCharacter() + " ";
                    }

                    Console.Write(str);


                }
                Console.Write("|");
            }

            Console.WriteLine();
            Console.WriteLine(" ---------------------------------");
            Console.WriteLine("   A   B   C   D   E   F   G   H");
            Console.WriteLine(game.WhoseTurn);
        }
        static void Main(string[] args)
        {
            bool isValid;
            string fen = "k7/4r3/8/8/4R3/8/8/K7 w - - 0 1";
            ChessGame game = new ChessGame(fen);
            Player me = Player.White;
            while (!game.IsGameOver())
            {
                DrawBoard(game);
                if (game.WhoseTurn == me)
                {
                    Move move;
                    do
                    {
                        string from = Console.ReadLine();
                        string to = Console.ReadLine();
                        move = new Move(from, to, me);
                        if ((move.NewPosition.Rank == 1 && move.Player == Player.Black) || (move.NewPosition.Rank == 8 && move.Player == Player.White))
                            move.Promotion = 'Q';
                        isValid = game.IsValidMove(move);
                    } while (!isValid);
                    move.Promotion = null;
                    game.ApplyMove(move, true);
                }
                else
                {
                    string from = Console.ReadLine();
                    string to = Console.ReadLine();
                    Move move = new Move(from, to, game.WhoseTurn);
                    isValid = game.IsValidMove(move);
                    if (!isValid)
                    {
                        Console.WriteLine("Invalid move");
                    }
                    game.ApplyMove(move, true);
                }
            }
            if (game.DrawClaimed && game.DrawByRepitition)
            {
                Console.WriteLine("Draw");
                Console.WriteLine("Board State Repeated 3 times.");
            }
            else if (game.DrawClaimed && !game.DrawByRepitition)
            {
                Console.WriteLine("Draw");
                Console.WriteLine(game.DrawReason);
            }
            else if (game.IsWinner(me))
            {
                Console.WriteLine("You win");

            }
            else
            {
                Console.WriteLine("You lose");
            }
            Console.Read();
        }
    }
}
