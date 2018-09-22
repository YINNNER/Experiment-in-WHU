using CCWin;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Fund
{
    partial class Form1 : CCSkinMain  //tab3函数----股票排行
    {
        //显示表格股票排行
        void GetIntroductionForm4()
        {
            //前100名股票
            string str = ReadTab3(1);
            string[] all = str.Split(',');
            for (int i = 0; i < 100; i++)
            {
                DataGridViewRow row1 = new DataGridViewRow();

                this.Invoke((EventHandler)delegate
                {
                    dataGridView2.Rows.Add(row1);
                    dataGridView2.Rows[i].Cells[0].Value = i + 1;
                    dataGridView2.Rows[i].Cells[1].Value = all[i * 2];

                    double d = Convert.ToDouble(all[i * 2 + 1]);
                    d = Math.Round(d, 2);
                    dataGridView2.Rows[i].Cells[2].Value = d;
                });  
            }

            //后100名股票
            str = ReadTab3(2);
            all = str.Split(',');
            for (int i = 0; i < 100; i++)
            {
                DataGridViewRow row2 = new DataGridViewRow();

                this.Invoke((EventHandler)delegate
                {
                    skinDataGridView3.Rows.Add(row2);
                    skinDataGridView3.Rows[i].Cells[0].Value = i + 1;
                    skinDataGridView3.Rows[i].Cells[1].Value = all[i * 2];

                    double d = Convert.ToDouble(all[i * 2 + 1]);
                    d = Math.Round(d, 2);
                    skinDataGridView3.Rows[i].Cells[2].Value = d;
                });
            }
        }

        //读取result.txt中的股票排行
        string ReadTab3(int num)
        {
            StreamReader sr = new StreamReader("../../stock/result/result" + num + ".txt", Encoding.Default);
            String data = sr.ReadToEnd();
            return data;
        }

    }
}
