using System;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using CCWin;

namespace Fund
{
    public partial class Form1 : CCSkinMain //主界面
    {
        //声明成员变量---存放基金、股票的html信息
        private List<string> fundHtmls;
        private List<string> stockHtmls3;
        private List<string> stockHtmls2;
        private List<double> stockPositions;

        //线程锁
        private object locker;

        //初始化页数
        private int page = 1;

        //声明成员变量
        private bool[] status;
        private List<Stock> stocks;
        private Thread td; //线程

        //初始化开始界面，并把页数转到第一页
        public Form1()
        {
            //初始化成员变量
            stocks = new List<Stock>();
            fundHtmls = new List<string>();
            fundHtmls.Capacity = 1400;
            stockHtmls3 = new List<string>();
            stockHtmls3.Capacity = 1500;
            stockHtmls2 = new List<string>();
            stockHtmls2.Capacity = 1500;
            stockPositions = new List<double>();
            stockPositions.Capacity = 1500;
            status = new bool[55];
            locker = new object();

            //初始化部件
            InitializeComponent();
            //开线程操作
            ThreadStart ts = GetIntroduction;
            td = new Thread(ts);
            td.SetApartmentState(ApartmentState.STA);
            td.Start();
        }

        //主界面进去显示第1页
        private void GetIntroduction()
        {
            turnTo(1);
        }

        //获取网页的内容，代码来自老师给的股票
        protected string GetContent(string url, string str = "UTF8")
        {
            var html = "";
            // 发送查询请求
            // Create a request for the URL. 	
            var request = (HttpWebRequest)WebRequest.Create(url);
            var proxy=new WebProxy("58.220.95.107",8080);
            request.Proxy = proxy;
            //设置浏览器header------伪装成浏览器
            request.Method = "get";
            request.UserAgent = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.108 Safari/537.36";
            request.KeepAlive = true;
            HttpWebResponse response = null;
            try
            {
                response = (HttpWebResponse)request.GetResponse();
                // 获得流
                StreamReader sr;
                if (str == "UTF8")
                    sr = new StreamReader(response.GetResponseStream(), Encoding.UTF8);
                else
                    sr = new StreamReader(response.GetResponseStream(), Encoding.GetEncoding("GB2312"));
                html = sr.ReadToEnd();
                response.Close();
            }
            catch (Exception ex)
            {
                // 本机没有联网
                if (ex.GetType().ToString().Equals("System.Net.WebException"))
                    MessageBox.Show("请检查你的计算机是否已连接上互联网。\n" + url, "提示");
            }
            return html;
        }

        //key：转到特定页
        private void turnTo(int pi)
        {
            //清空之前内容
            Invoke((EventHandler)delegate
            {
                dataGridView1.Rows.Clear();
            });
            var url =
                "http://fund.eastmoney.com/data/rankhandler.aspx?op=ph&dt=kf&ft=all&rs=&gs=0&sc=zzf&st=desc&sd=2015-10-29&ed=2016-10-29&qdii=&tabSubtype=,,,,,&pi="
                + pi + "&pn=50&dx=1&v=0.10850418109563731";

            var data = GetContent(url);
            //正则表达式，提取每两个引号之间内容
            var re = new Regex("(?<=\").*?(?=\")", RegexOptions.None);

            //用正则表达式提取内容
            var mc = re.Matches(data);

            var index = 0;

            //跳过单数项-----跳过","，由于正则提取两个引号之间，每个引号都和前一个引号匹配一次，故逗号也被提取了
            var pass = 0;

            foreach (Match funds in mc)
            {
                if (pass % 2 == 1)
                {
                    pass++;
                    continue;
                }

                var fund = funds.Value;
                //把逗号之间的内容提取出来放进string数组里
                var all = Regex.Split(fund, ",", RegexOptions.IgnoreCase);
                //新建一行
                var row = new DataGridViewRow();


                //之后的代码都是把string数组的内容放进每一行里
                Invoke((EventHandler)delegate
               {
                   dataGridView1.Rows.Add(row);
                   dataGridView1.Rows[index].Cells[0].Value = all[0];
                   dataGridView1.Rows[index].Cells[1].Value =
                       all[1].Substring(0, all[1].Length > 6 ? 6 : all[1].Length);
                   dataGridView1.Rows[index].Cells[2].Value = all[3].Length == 0 ? "---" : all[3].Substring(5);
                   dataGridView1.Rows[index].Cells[3].Value = all[4].Length == 0 ? "---" : all[4];
                   for (var i = 5; i < 15; i++)
                       dataGridView1.Rows[index].Cells[i].Value = getPecent(all[i + 1]);
                   dataGridView1.Rows[index].Cells[15].Value = all[20];
               });
                //换行
                index++;
                pass++;
            }


            Invoke(new EventHandler(delegate (object sender, EventArgs args)
            {
                //改变页码
                page = pi;
                label1.Text = page + "/55";

                //禁用按钮
                if (pi == 55)
                    button2.Enabled = false;
                else
                    button2.Enabled = true;

                if (pi == 1)
                    button1.Enabled = false;
                else
                    button1.Enabled = true;

                //清空文字框内容
                textBox1.Text = "";
            }));


        }

        //获得两位有效数字的字符串百分数
        private string getPecent(string temp)
        {
            if (temp.Length == 0)
                return "---";
            var d = Math.Round(Convert.ToDouble(temp), 2); //四舍六入五凑偶，注意，小数最后一位是0不会被保留的
            temp = d.ToString();
            //为了保证数据都保留两位小数，因此得到整数要补零
            if (Convert.ToInt32(d) - d == 0)
                temp += ".00%";
            else if (Convert.ToInt32(d * 10) - d * 10 == 0)
                temp += "0%";
            else
                temp += "%";
            return temp;
        }

        //下一页
        private void button2_Click(object sender, EventArgs e)
        {
            if (page == 55)
            {
                MessageBox.Show("已经到最后一页啦！", "提示");
                return;
            }
            turnTo(page + 1);
        }

        //上一页
        private void button1_Click(object sender, EventArgs e)
        {
            if (page == 1)
            {
                MessageBox.Show("已经到第一页啦！", "提示");
                return;
            }
            turnTo(page - 1);
        }

        //转到特定页
        private void button3_Click(object sender, EventArgs e)
        {
            //使用try catch通过文字框内容转到特定页，并抛出错误输出
            try
            {
                var a = Convert.ToInt32(textBox1.Text);
                if (!(a > 0 && a < 56))
                    throw new Exception();
                turnTo(a);
            }
            catch (Exception ex)
            {
                MessageBox.Show("输入错误，请检查您输入的数字（1-55）。", "提示");
                textBox1.Text = "";
                textBox1.Enabled = true;
                textBox2.Enabled = true;
                button2.Enabled = true;
                button3.Enabled = true;
                button5.Enabled = true;
            }
        }
       
        //查看某只基金详情
        private void dataGridView1_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            //var f = new Form2(dataGridView1.Rows[e.RowIndex].Cells[0].Value.ToString());
            //f.Show();
            skinTabControl1.SelectTab(1);
            textBox2.Text = dataGridView1.Rows[e.RowIndex].Cells[0].Value.ToString();
            button5_Click(sender, e);
        }

        

        //切换窗口标签tab
        private void skinTabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //tab3,4,5显示数据表格
            Thread td;
            ThreadStart ts = null;
            switch (skinTabControl1.SelectedTab.Name)
            {
                //查看股票排行
                case "skinTabPage3":
                    if (dataGridView2.Rows.Count > 0)
                        break;
                    ts = new ThreadStart(GetIntroductionForm4);
                    td = new Thread(ts);
                    td.SetApartmentState(ApartmentState.STA);
                    td.Start();
                    break;
                //查看增持前50的股票
                case "skinTabPage4":
                    if (skinDataGridView1.Rows.Count > 0)
                        break;
                    ts = new ThreadStart(GetIntroductionForm5);
                    td = new Thread(ts);
                    td.SetApartmentState(ApartmentState.STA);
                    td.Start();
                    break;
                //查看减持前50的股票
                case "skinTabPage5":
                    if (skinDataGridView2.Rows.Count > 0)
                        break;
                    ts = new ThreadStart(GetIntroductionForm6);
                    td = new Thread(ts);
                    td.SetApartmentState(ApartmentState.STA);
                    td.Start();
                    break;
                //tab1,2不执行操作
                default:
                    break;
            }

        }

        //切换tab2次级窗口标签
        private void skinTabControl2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (skinTabControl2.SelectedTab.Name == "skinTabPage6")
            {
                if(dataGridView3.Rows.Count==0)
                MessageBox.Show("该基金没有持仓的股票！");
            }
            
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            //skinEngine1.SkinFile = @"..\..\resources\Calmness.ssk";
            skinTabControl1.SelectedIndex = 0;
            skinTabControl2.SelectedIndex = 0;
            skinTabControl3.SelectedIndex = 0;
        }

    }

    public class Stock
    {
        public string name { get; set; }
        public decimal sum { get; set; }
        public string number { get; set; }
        public decimal balance { get; set; }
        public bool isVisited { get; set; }
        public string stockHtmls2 { get; set; }
        public string stockHtmls3 { get; set; }
    }
}