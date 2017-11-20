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
    class speechPromotion
    {
        //declarations
        SpeechSynthesizer ss;
        SpeechRecognitionEngine sre;
        SpeechRecognitionEngine cofnirmsre;
        Choices clist;
        Choices cofnirmlist;
        List<String> possiblePromotions;
        Grammar gr, cofnirmgr;
        String lastOrder;
        bool confirm;
        bool wait;
        bool wait2;
        bool entered1 = false;
        bool entered2 = false;

        public speechPromotion()
        {
            ss = new SpeechSynthesizer();
            sre = new SpeechRecognitionEngine();
            cofnirmsre = new SpeechRecognitionEngine();
            clist = new Choices();
            cofnirmlist = new Choices();
            possiblePromotions = new List<String>();
            lastOrder = "-1";
            confirm = false;
            wait = true;
            wait2 = true;
            possiblePromotions.Add("queen");
            possiblePromotions.Add("knight");
            possiblePromotions.Add("rook");
            possiblePromotions.Add("bishop");

            clist.Add(possiblePromotions.ToArray());
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

        }

        public string newPromotion()
        {
            wait2 = true;
            Console.WriteLine("Please say what do you want to promote to\n \"queen\", \"knight\",\"rook\",\"bishop\" ");
            try
            {
                entered1 = false;
                sre.Recognize();
                while (!entered1)
                {
                    Console.WriteLine("I didn't hear you please you say it again");
                    newPromotion();
                }

            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            while (wait2) ;
            return lastOrder;
        }
        void sre_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            entered1 = true;
            foreach (var pm in possiblePromotions)
                if (pm == e.Result.Text.ToString())
                {
                    Console.WriteLine("are you sure to promote to " + e.Result.Text.ToString() + " ? ");
                    ss.Speak("are you sure to promote to " + e.Result.Text.ToString());
                    wait = true;
                    entered2 = false;
                    while(!entered2)
                    {
                        Console.WriteLine("I didn't hear you please you say it again");
                        cofnirmsre.Recognize();
                    }
                    while (wait) ;
                    if (confirm)
                    {
                        lastOrder = pm;
                        Console.WriteLine("the garunteed result is \"" + e.Result.Text.ToString() + "\"");
                        wait2 = false;
                    }
                    else
                    {
                        lastOrder = "-1";
                        newPromotion();
                    }
                    return;
                }
            Console.WriteLine("not found");
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
