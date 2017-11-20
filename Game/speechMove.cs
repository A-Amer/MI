using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Speech;
using System.Speech.Synthesis;
using System.Speech.Recognition;
using System.Threading;


namespace MI_Speech
{
    class speechMove
    {
        //declarations
        SpeechSynthesizer ss = new SpeechSynthesizer();
        SpeechRecognitionEngine sre = new SpeechRecognitionEngine();
        SpeechRecognitionEngine cofnirmsre = new SpeechRecognitionEngine();
        Choices clist = new Choices();
        Choices cofnirmlist = new Choices();
        List<String> possibleMoves = new List<String>();
        Grammar gr, cofnirmgr;
        String lastOrder = "-1";
        bool confirm = false;
        bool wait = true;
        bool wait2 = true;
        bool entered1 = false;
        bool entered2 = false;

        public speechMove()
        {
            for (char i = 'A'; i <= 'H'; i++)
                for (int j = 1; j < 9; j++)
                    for (char x = 'A'; x <= 'H'; x++)
                        for (int y = 1; y < 9; y++)
                            if (!(i == x && j == y))
                                possibleMoves.Add("move " + i + " " + j.ToString() + " to " + x + " " + y.ToString());
            clist.Add(possibleMoves.ToArray());
            cofnirmlist.Add(new string[] { "yes", "no" });
            gr = new Grammar(new GrammarBuilder(clist));
            cofnirmgr = new Grammar(new GrammarBuilder(cofnirmlist));
            sre.RequestRecognizerUpdate();
            sre.LoadGrammar(gr);
            sre.SpeechRecognized += sre_SpeechRecognized;
            sre.SetInputToDefaultAudioDevice();

            cofnirmsre.RequestRecognizerUpdate();
            cofnirmsre.LoadGrammar(cofnirmgr);
            cofnirmsre.SpeechRecognized += cofnirmsre_SpeechRecognized;
            cofnirmsre.SetInputToDefaultAudioDevice();
            //txtContents.Text += possibleMoves.Count + Environment.NewLine; must give 4032 ( 64 * 63 )
        }

        public string newMove()
        {
            wait2 = true;
            Console.WriteLine("Please say your action");
            try
            {
                entered1 = false;
                sre.Recognize();
                while (!entered1)
                {
                    Console.WriteLine("I didn't hear you please you say it again");
                    sre.Recognize();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            while (wait2);
            return lastOrder;
        }

        void sre_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            entered1 = true;
            sre.RecognizeAsyncStop();
            foreach (var pm in possibleMoves)
                if (pm == e.Result.Text.ToString())
                {
                    Console.WriteLine("are you sure to " + e.Result.Text.ToString() + " ? ");
                    ss.Speak("are you sure to " + e.Result.Text.ToString());
                    wait = true;
                    entered2 = false;
                    while (!entered2)
                    {
                        Console.WriteLine("I didn't hear you please you say it again");
                        cofnirmsre.Recognize();
                    }
                    while (wait) ;
                    if (confirm)
                    {
                        lastOrder = pm.Substring(5, 1) + pm.Substring(7, 1) + pm.Substring(12, 1) + pm.Substring(14, 1);
                        Console.WriteLine("the garunteed result is \"" + e.Result.Text.ToString() + "\"");
                        wait2 = false;
                    }
                    else
                    {
                        lastOrder = "-1";
                        newMove();
                    }
                    return;
                }
        }

        void cofnirmsre_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            entered2 = true;
            switch (e.Result.Text.ToString())
            {
                case "yes":
                    confirm = true;
                    break;
                case "no":
                    confirm = false;
                    break;
            }
            wait = false;
            Console.WriteLine(e.Result.Text.ToString());
            return;
        }
    }
}