using System;
using CCWin;
using System.Threading;
using System.Windows.Forms;

namespace Fund
{
    partial class Form1 : CCSkinMain  //tab2函数----基金信息及基金持仓
    {
        private bool UrlIsExist(String url)
        {
            System.Uri u = null;
            try
            {
                u = new Uri(url);
            }
            catch { return false; }
            bool isExist = false;
            System.Net.HttpWebRequest r = System.Net.HttpWebRequest.Create(u)
                                    as System.Net.HttpWebRequest;
            r.Method = "HEAD";
            try
            {
                System.Net.HttpWebResponse s = r.GetResponse() as System.Net.HttpWebResponse;
                if (s.StatusCode == System.Net.HttpStatusCode.OK)
                {
                    isExist = true;
                }
            }
            catch (System.Net.WebException x)
            {
                try
                {
                    isExist = ((x.Response as System.Net.HttpWebResponse).StatusCode !=
                                 System.Net.HttpStatusCode.NotFound);
                }
                catch { isExist = (x.Status == System.Net.WebExceptionStatus.Success); }
            }
            return isExist;
        }

        //输入基金代码查看某只基金详情
        private void button5_Click(object sender, EventArgs e)
        {
            var str = textBox2.Text;

            //通过try catch把输入的基金代码转到网页，若网页不存在，则抛出错误，
            //同时把输入的错误基金代号的格式抛出
            try
            {
                if (!UrlIsExist("http://fund.eastmoney.com/" + str + ".html"))
                {
                    throw new Exception("UrlIsNotExist");
                }
                
                var x = GetContent(@"http://fund.eastmoney.com/" + str + ".html");
                x = x.Substring(x.IndexOf("<title>"));
                x = x.Substring(0, x.IndexOf("</title>"));
                if (!x.Contains(str))
                    throw new Exception();
                string id = str;

                //给tab2增加内容
                pictureBox1.ImageLocation = @"http://j4.dfcfw.com/charts/pic6/" + id + ".png";

                //通过string的substring和IndexOf方法处理字符串，获取文字内容，并放入文字框
                string result = GetContent(@"http://fund.eastmoney.com/" + id + ".html");
                try
                {
                    result = result.Substring(result.IndexOf("id=\"gz_gsz\">"));
                    string tmp = result.Substring(result.IndexOf("\">") + 2);
                    tmp = tmp.Substring(0, tmp.IndexOf("<"));
                    textBox5.Text = tmp;

                    result = result.Substring(result.IndexOf("ui-font-large") + 1);
                    tmp = result.Substring(result.IndexOf("\">") + 2);
                    tmp = tmp.Substring(0, tmp.IndexOf("<"));
                    textBox4.Text = tmp;

                    result = result.Substring(result.IndexOf("ui-font-large"));
                    tmp = result.Substring(result.IndexOf("\">") + 2);
                    tmp = tmp.Substring(0, tmp.IndexOf("<"));
                    textBox3.Text = tmp;

                    result = result.Substring(result.IndexOf("<table>"));
                    result = result.Substring(result.IndexOf("<td>") + 4);
                    result = result.Substring(result.IndexOf(">") + 1);
                    tmp = result.Substring(0, result.IndexOf("</a>"));
                    result = result.Substring(result.IndexOf("|&nbsp;&nbsp;") + 13);
                    tmp += " | " + result.Substring(0, result.IndexOf("<"));
                    label6.Text = tmp;

                    result = result.Substring(result.IndexOf("基金规模"));
                    result = result.Substring(result.IndexOf("：") + 1);
                    tmp = result.Substring(0, result.IndexOf("<"));
                    label8.Text = tmp;

                    result = result.Substring(result.IndexOf("基金经理"));
                    result = result.Substring(result.IndexOf(">") + 1);
                    tmp = result.Substring(0, result.IndexOf("<"));
                    label10.Text = tmp;

                    result = result.Substring(result.IndexOf("日"));
                    result = result.Substring(result.IndexOf("：") + 1);
                    tmp = result.Substring(0, result.IndexOf("<"));
                    label12.Text = tmp;

                    result = result.Substring(result.IndexOf("人"));
                    result = result.Substring(result.IndexOf("：") + 1);
                    result = result.Substring(result.IndexOf(">") + 1);
                    tmp = result.Substring(0, result.IndexOf("<"));
                    label14.Text = tmp;

                    //查看基金持仓情况
                    dataGridView3.Rows.Clear();
                    ParameterizedThreadStart ts = new ParameterizedThreadStart(GetIntroductionForm3);
                    td = new Thread(ts);
                    td.SetApartmentState(ApartmentState.STA);
                    td.Start(id);

                }
                catch (Exception)
                {
                    MessageBox.Show("此基金处于认购期不存在信息", "提示");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("输入错误，不存编号为" + str + "的基金。", "提示");
                textBox1.Text = "";
                textBox1.Enabled = true;
                textBox2.Enabled = true;
                button1.Enabled = true;
                button2.Enabled = true;
                button3.Enabled = true;
                button5.Enabled = true;
            }
        }

        //查看基金持仓情况
        void GetIntroductionForm3(object ID)
        {
            string url = @"http://fund.eastmoney.com/f10/FundArchivesDatas.aspx?type=jjcc&code=" + (string)ID + "&topline=10&year=&month=&rt=0.029766627475606988";

            string data = GetContent(url);
            //如果没有表格内容，则返回
            //string的contain方法是判断字符串是否有一段特定的字符
            if (!data.Contains("<tbody>"))
                return;

            if (!data.Contains("市场"))
            {
                data = data.Substring(data.IndexOf("<tbody>") + 7);
                data = data.Substring(0, data.IndexOf("</tbody>"));
                int index = 0;
                string tmp;
                //处理字符串，获取需要的信息
                while (data.Contains("<tr>"))
                {

                    DataGridViewRow row = new DataGridViewRow();

                    data = data.Substring(data.IndexOf("<td>") + 4);
                    tmp = data.Substring(0, data.IndexOf("<"));
                    this.Invoke((EventHandler)delegate
                    {
                        dataGridView3.Rows.Add(row);
                        dataGridView3.Rows[index].Cells[0].Value = tmp;
                    });

                    data = data.Substring(data.IndexOf("<td>") + 4);
                    tmp = data.Substring(data.IndexOf(">") + 1);
                    //tmp = tmp.Substring(0, tmp.IndexOf("</a"));
                    tmp = tmp.Substring(0, tmp.IndexOf("<"));
                    this.Invoke((EventHandler)delegate
                    {
                        dataGridView3.Rows[index].Cells[1].Value = tmp;
                    });

                    data = data.Substring(data.IndexOf("<td"));
                    data = data.Substring(data.IndexOf(">") + 1);
                    tmp = data.Substring(data.IndexOf(">") + 1);
                    tmp = tmp.Substring(0, tmp.IndexOf("<"));
                    this.Invoke((EventHandler)delegate
                    {
                        dataGridView3.Rows[index].Cells[2].Value = tmp;
                    });

                    //跳过无用数据
                    data = data.Substring(data.IndexOf("<td") + 3);
                    data = data.Substring(data.IndexOf("<td") + 3);
                    data = data.Substring(data.IndexOf("<td") + 3);


                    data = data.Substring(data.IndexOf("<td") + 3);
                    tmp = data.Substring(data.IndexOf(">") + 1);
                    tmp = tmp.Substring(0, tmp.IndexOf("<"));
                    this.Invoke((EventHandler)delegate
                    {
                        dataGridView3.Rows[index].Cells[3].Value = tmp;
                    });

                    data = data.Substring(data.IndexOf("<td") + 3);
                    tmp = data.Substring(data.IndexOf(">") + 1);
                    tmp = tmp.Substring(0, tmp.IndexOf("<"));
                    this.Invoke((EventHandler)delegate
                    {
                        dataGridView3.Rows[index].Cells[4].Value = tmp;
                    });

                    data = data.Substring(data.IndexOf("<td"));
                    tmp = data.Substring(data.IndexOf(">") + 1);
                    tmp = tmp.Substring(0, tmp.IndexOf("<"));
                    this.Invoke((EventHandler)delegate
                    {
                        dataGridView3.Rows[index].Cells[5].Value = tmp;
                    });
                    index++;
                }
            }
            else
            {
                data = data.Substring(data.IndexOf("<tbody>") + 7);
                data = data.Substring(0, data.IndexOf("</tbody>"));
                int index = 0;
                while (data.Contains("<tr>"))
                {

                    DataGridViewRow row = new DataGridViewRow();
                    this.Invoke((EventHandler)delegate
                    {
                        dataGridView3.Rows.Add(row);
                    });
                    for (int i = 0; i < 6; i++)
                    {
                        data = data.Substring(data.IndexOf("<td") + 3);
                        data = data.Substring(data.IndexOf(">") + 1);
                        string tmp = data.Substring(0, data.IndexOf("<"));
                        this.Invoke((EventHandler)delegate
                        {
                            dataGridView3.Rows[index].Cells[i].Value = tmp;
                        });
                    }
                    index++;
                }
            }
        }
    }
}
