using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.IO;

namespace Fund
{
    public partial class Form6 : Form
    {
        Thread td;
        public Form6()
        {
            InitializeComponent();
            ThreadStart ts = new ThreadStart(GetIntroduction);
            td = new Thread(ts);
            td.SetApartmentState(ApartmentState.STA);
            td.Start();
        }

        private void skinDataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        void GetIntroduction()
        {
            string str = Read();
            string[] all = str.Split(',');
            for (int i = 0; i < 50; i++)
            {
                DataGridViewRow row = new DataGridViewRow();

                this.Invoke((EventHandler)delegate
                {
                    skinDataGridView1.Rows.Add(row);
                    skinDataGridView1.Rows[i].Cells[0].Value = all[i * 3];
                    skinDataGridView1.Rows[i].Cells[1].Value = all[i * 3 + 1];
                    double d = Convert.ToDouble(all[i * 3 + 2]);
                    d = Math.Round(d, 2);
                    skinDataGridView1.Rows[i].Cells[2].Value = d;
                });
            }
        }

        string Read()
        {
            StreamReader sr = new StreamReader("../../stock/result/balanceResult2.txt", Encoding.Default);
            String data = sr.ReadToEnd();
            return data;
        }
    }
}
