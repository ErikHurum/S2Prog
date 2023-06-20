using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Arrange_measure_data
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void btnReadFile_Click(object sender, EventArgs e)
        {
            {
                string filename;
                filename = txtFileName.Text;
                //Oppretteren en FileStream for den aktuelle filen (filename):
                FileStream inputstream = new FileStream(filename, FileMode.Open, FileAccess.Read);
                //Oppretteren et StreamReader-objekt for å lese fra en tekstfil:
                StreamReader streamreader = new StreamReader(inputstream);

                string line = "";
                while ((line = streamreader.ReadLine()) != null)
                {
                    //Finner plasseringen (indeksnummeret) til skilletegnet (kommaet) i teksten, så  
                    //dataene før og etter dette tegnet kan separeres ut og lagres i to variabler
                    int delimitersIndexNumber = line.IndexOf(",");
                    string part1 = line.Substring(0, delimitersIndexNumber);
                    DateTime x1 = DateTime.Parse(part1);
                    string part2 = line.Substring(delimitersIndexNumber + 1,
                                   line.Length - (delimitersIndexNumber + 1));
                    part2 = part2.Replace(".", ",");
                    double y1 = Convert.ToDouble(part2);
                    x1Values.Add(x1);
                    y1Values.Add(y1);

                    chart1.Series["Series1"].Points.DataBindXY(x1Values, y1Values);
                }
                streamreader.Close();//Husk å stenge streamen/fila
            }
        }
    }
}
