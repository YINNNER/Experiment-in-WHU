using CCWin;
using System;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace Fund
{
    partial class Form1 : CCSkinMain  //tab4、5函数----增仓、减仓股票前50排名
    {
        //显示表格股票增仓排名
        void GetIntroductionForm5()
        {
            string str = Read(1);
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

        //显示表格股票减仓排名
        void GetIntroductionForm6()
        {
            string str = Read(2);
            string[] all = str.Split(',');
            for (int i = 0; i < 50; i++)
            {
                DataGridViewRow row = new DataGridViewRow();

                this.Invoke((EventHandler)delegate
                {
                    skinDataGridView2.Rows.Add(row);
                    skinDataGridView2.Rows[i].Cells[0].Value = all[i * 3];
                    skinDataGridView2.Rows[i].Cells[1].Value = all[i * 3 + 1];
                    double d = Convert.ToDouble(all[i * 3 + 2]);
                    d = Math.Round(d, 2);
                    skinDataGridView2.Rows[i].Cells[2].Value = d;
                });
            }
        }

        //读取balanceResult1、2文档
        string Read(int num)
        {
            StreamReader sr = new StreamReader("../../stock/result/balanceResult" + num + ".txt", Encoding.Default);
            String data = sr.ReadToEnd();
            return data;
        }
    }
}
