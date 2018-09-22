using CCWin;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Fund
{
    partial class Form1 : CCSkinMain //更新数据函数
    {
        //更新股票数据，并计算股票总金额排名，最后将结果写入result.txt中
        private void button4_Click(object sender, EventArgs e)
        {
            ThreadStart ts = new ThreadStart(Update);
            td = new Thread(ts);
            td.Start();
        }

        private void Update()
        {
            //主线程显示进度条
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Maximum = 55;
                skinProgressBar1.Visible = true;
                skinLabel1.Visible = true;
            });
            
            //爬取基金网页
            Task[] tasks1 = new Task[25];
            for (int i = 0; i < tasks1.Length; i++)
            {
                tasks1[i] = new Task(n => GetFundHtmls(), 0);
                tasks1[i].Start();
            }
            Task.WaitAll(tasks1);
            
            //计算股票控股总金额
            CalculateStocksSum();

            //进度条重置为0，label文字改变
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Maximum = stocks.Count;
                skinProgressBar1.Value = 0;
                skinLabel1.Text = "正在爬取股票网页……";
            });

            //爬取股票网页
            Task[] tasks = new Task[25];
            for (int i = 0; i < tasks.Length; i++)
            {
                tasks[i] = new Task(n => GetStockHtmls(), 0);
                tasks[i].Start();
            }
            Task.WaitAll(tasks);

            //进度条重置，显示处理数据
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Maximum = 5;
                skinProgressBar1.Value = 0;
                skinLabel1.Text = "正在处理数据……";
            });

            //得到基金持仓差额
            GetBalances();

            //进度条更新，显示写入数据
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Value++;
                skinLabel1.Text = "正在写入数据……";
            });

            //股票总金额排名,并将股票总金额排名结果写入result.txt文档
            WriteResult(RankStocks());

            //基金控股差额排名,并将基金控股差额排名结果写入balanceResult.txt文档
            WriteBalanceResult(RankPositionBalance());
            
            //完成------进度条，label消失
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Visible = false;
                skinLabel1.Visible = false;

                //显示完成提示
                MessageBox.Show("更新数据完毕");
            });

        }


        //线程信息，用于调试
        static void ThreadMessage(string data)
        {

            string message = string.Format("{0}\n  CurrentThreadId is {1}",
                                 data, Thread.CurrentThread.ManagedThreadId);
            Console.WriteLine(message);
        }

        //得到所有股票的html
        private void GetFundHtmls()
        {

            ThreadMessage("Spider Thread");
            
            
            //将每一页中的基金ID信息都提取出来
            for (var i = 0; i < 55; i++)
            {
                //线程同步：上锁，防止数据污染----多个线程同时进入同一个i
                lock (locker)
                {
                    if (status[i]) continue;
                    //状态变为true表示该页面已经爬过了
                    status[i] = true;
                }
                Console.WriteLine(i);

                //进度条+1
                this.Invoke((EventHandler)delegate 
                {
                    skinProgressBar1.Value++;
                });

                var url =
                    "http://fund.eastmoney.com/data/rankhandler.aspx?op=ph&dt=kf&ft=all&rs=&gs=0&sc=zzf&st=desc&sd=2015-10-29&ed=2016-10-29&qdii=&tabSubtype=,,,,,&pi="
                    + i + "&pn=50&dx=1&v=0.10850418109563731";

                var data = GetContent(url);
                //正则表达式，提取每两个引号之间内容
                var re = new Regex("(?<=\").*?(?=\")", RegexOptions.None);

                //用正则表达式提取内容
                var mc = re.Matches(data);
                //获得基金的ID，并爬取每个基金对应的网页
                string url2;
                string HTML;

                foreach (Match funds in mc)
                {
                    var fund = funds.Value;
                    //把逗号之间的内容提取出来放进string数组里
                    var all = Regex.Split(fund, ",", RegexOptions.IgnoreCase);
                    if (all[0].Length == 0)
                        continue;
                    //fundsID.Add(all[0]);

                    //将每条基金对应的网页信息写入对应fundHtmls这个成员变量string数组中
                    //all[0]为基金ID
                    url2 = "http://fund.eastmoney.com/" + all[0] + ".html";
                    HTML = GetContent(url2);
                    if (HTML != "")
                        fundHtmls.Add(HTML);
                }
            }
            
        }

        //数据分析：读取每一个基金文件中的信息并计算每个股票的总金额
        private void CalculateStocksSum()
        {
            string content;
            string total, pecent;
            decimal sums;

            //进度条重置，显示处理数据
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Maximum = fundHtmls.Count;
                skinProgressBar1.Value = 0;
                skinLabel1.Text = "正在处理数据……";
            });

            foreach (var html in fundHtmls)
            {
                //获得基金规模并存入sums中
                content = html;
                content = content.Substring(content.IndexOf("基金规模") + 9);
                total = content.Substring(0, content.IndexOf("亿"));
                if (total == "--")
                    continue;
                sums = Convert.ToDecimal(total);


                content = content.Substring(content.IndexOf("股票名称"));
                content = content.Substring(0, content.IndexOf("</table>"));
                //获得该基金购买的所有股票信息
                while (content.Contains("alignLeft"))
                {
                    content = content.Substring(content.IndexOf("alignLeft"));
                    content = content.Substring(content.IndexOf(">") + 4);
                    var tmp1 = content.Substring(0, 2);
                    string stocksNum = null;
                    if (tmp1 == "<a")
                    {
                        //排除非大陆股票
                        stocksNum = content.Substring(content.IndexOf(".html") - 6);
                        Regex rex = new Regex("[0-9]{6}");
                        Match ma = rex.Match(stocksNum);
                        //判断是否为美股、港股
                        if (ma.Success)
                        {
                            stocksNum = ma.ToString();
                            content = content.Substring(content.IndexOf(">") + 1);
                        }

                        else
                        {
                            content = content.Substring(content.IndexOf(">") + 1);
                            stocksNum = "";
                        }

                    }
                    //排除台股
                    if (tmp1 == "<d")
                    {
                        content = content.Substring(content.IndexOf(">") + 1);
                        stocksNum = "";
                    }

                    //获得股票名称
                    var stockName = content.Substring(0, content.IndexOf("<"));
                    content = content.Substring(content.IndexOf("alignRight"));
                    content = content.Substring(content.IndexOf(">") + 1);
                    //持仓占比
                    pecent = content.Substring(0, content.IndexOf("<") - 1);
                    //购买股票金额=基金规模*股票持仓占比
                    sums *= Convert.ToDecimal(pecent) / 100.0M;
                    var matchs = false;
                    foreach (var sto in stocks)
                    {
                        if (sto.name == stockName)
                        {
                            sto.sum += sums;
                            matchs = true;
                            break;
                        }
                    }

                    if (!matchs)
                    {
                        var st = new Stock();
                        st.name = stockName;
                        st.sum = sums;
                        st.number = stocksNum;
                        stocks.Add(st);
                    }
                }

                //进度条重置，显示处理数据
                this.Invoke((EventHandler)delegate
                {
                    skinProgressBar1.Value++;
                });
            }

        }

        //得到所有股票的html
        private void GetStockHtmls()
        {
            string html;
            
            foreach (Stock stock in stocks)
            {
                lock (locker)
                {
                    if (stock.isVisited) continue;
                    stock.isVisited = true;
                   
                }

                //进度条+1
                this.Invoke((EventHandler)delegate
                {
                    skinProgressBar1.Value++;
                });


                if (stock.number == "" || stock.number == null)
                    continue;
                //三季度股票网页
                string url3 = "http://data.eastmoney.com/zlsj/detail/2017-09-30-1-" + stock.number + ".html";
                html = GetContent(url3, "GB18030");
                stock.stockHtmls3 = html;
                //二季度股票网页
                string url4 = "http://data.eastmoney.com/zlsj/detail/2017-06-30-1-" + stock.number + ".html";
                html = GetContent(url4, "GB18030");
                stock.stockHtmls2 = html;
                //打印股票代码用于调试
                Console.WriteLine(stock.number);
            }

        }

        //得到股票季度持仓差额
        private void GetBalances()
        {
            decimal position2, position3;

            foreach (var stock in stocks)
            {
                if (stock.number == "" || stock.number == null)
                    continue;
                //获取二季度基金持仓总数
                //使用正则获取基金持仓总数
                string regexString = "<td>基金</td><td>\\d+</td><td>(?<position2>.*?)</td>";
                Regex regex = new Regex(regexString);
                var match = regex.Match(stock.stockHtmls2);
                string position = match.Groups["position2"].Value;
                //排除无持仓信息的股票
                if (position == "")
                {
                    position2 = 0;
                }
                else
                {
                    position2 = Convert.ToDecimal (position);
                }
                stock.balance = position2;
                //获取三季度基金持仓总数
                regexString = "<td>基金</td><td>\\d+</td><td>(?<position3>.*?)</td>";
                regex = new Regex(regexString);
                match = regex.Match(stock.stockHtmls3);
                position = match.Groups["position3"].Value;
                //排除无持仓信息的股票
                if (position == "")
                {
                    position3 = 0;
                }
                else
                {
                    position3 = Convert.ToDecimal(position);
                }
                stock.balance -= position3;

            }

        }

        //基金控股差额排名
        private List<Stock> RankPositionBalance()
        {

            List<Stock> tmp = new List<Stock>();
            foreach (Stock st in stocks)
            {
                tmp.Add(st);
            }
            QuickSort2(tmp, 0, tmp.Count - 1);

            //进度条更新+1
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Value++;
            });

            return tmp;
        }

        //将基金控股差额排名结果写入balanceResult.txt文档
        private void WriteBalanceResult(List<Stock> tmp)
        {
            var result = "";
            //增持前五十
            for (var i = 0; i < 50; i++)
                result += tmp.ElementAt(i).number + "," + tmp.ElementAt(i).name + "," + tmp.ElementAt(i).balance + ",";

            //将结果写入balanceResult1.txt文档
            if (Environment.OSVersion.Platform == PlatformID.Unix)
                inText(result, "result/balanceResult1", "Default");
            else
                inText(result, "result\\balanceResult1", "Default");

            //清空result内容
            result = "";

            //减持前五十
            for (int i = tmp.Count - 1; i > tmp.Count - 51; i--)
            {
                result += tmp.ElementAt(i).number + "," + tmp.ElementAt(i).name + "," + tmp.ElementAt(i).balance + ",";
            }

            //将结果写入balanceResult2.txt文档
            if (Environment.OSVersion.Platform == PlatformID.Unix)
                inText(result, "result/balanceResult2", "Default");
            else
                inText(result, "result\\balanceResult2", "Default");

            //进度条更新+1
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Value++;
            });
        }

        //股票总金额排名
        private List<Stock> RankStocks()
        {
            List<Stock> tmp = new List<Stock>();
            foreach (Stock st in stocks)
            {
                tmp.Add(st);
            }
            //快速排序
            QuickSort1(tmp, 0, tmp.Count - 1);

            //进度条更新+1
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Value++;
            });
            return tmp;
        }

        //交换
        void Swap(List<Stock> list, int i, int j)
        {
            Stock temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
        //快排---股票总金额排名
        void QuickSort1(List<Stock> list, int low, int high)
        {
            if (low >= high) return;
            Stock temp = list[low];//哨兵
            int i = low + 1, j = high;
            while (true)
            {
                while (list[j].sum < temp.sum) j--;
                while (list[i].sum > temp.sum && i < j) i++;
                if (i >= j) break;
                Swap(list, i, j);
                i++; j--;
            }
            if (j != low) Swap(list, low, j);

            QuickSort1(list, j + 1, high);
            QuickSort1(list, low, i - 1);
        }
        //快排---基金控股差额排名
        void QuickSort2(List<Stock> list, int low, int high)
        {
            if (low >= high) return;
            Stock temp = list[low];//哨兵
            int i = low + 1, j = high;
            while (true)
            {
                while (list[j].balance < temp.balance) j--;
                while (list[i].balance > temp.balance && i < j) i++;
                if (i >= j) break;
                Swap(list, i, j);
                i++; j--;
            }
            if (j != low) Swap(list, low, j);

            QuickSort2(list, j + 1, high);
            QuickSort2(list, low, i - 1);
        }

        //将股票总金额排名结果写入result.txt文档
        private void WriteResult(List<Stock> tmp)
        {
            var result = "";
            //前100名股票
            for (var i = 0; i < 100; i++)
                result += tmp.ElementAt(i).name + "," + tmp.ElementAt(i).sum + ",";

            //将结果写入result.txt文档
            if (Environment.OSVersion.Platform == PlatformID.Unix)
                inText(result, "result/result1", "Default");
            else
                inText(result, "result\\result1", "Default");

            //清空result内容
            result = "";

            //后100名股票
            for (var i = tmp.Count-1; i > tmp.Count - 101; i--)
                result += tmp.ElementAt(i).name + "," + tmp.ElementAt(i).sum + ",";

            //将结果写入result.txt文档
            if (Environment.OSVersion.Platform == PlatformID.Unix)
                inText(result, "result/result2", "Default");
            else
                inText(result, "result\\result2", "Default");

            //进度条更新+1
            this.Invoke((EventHandler)delegate
            {
                skinProgressBar1.Value++;
            });
        }

        //将数据写入文件中
        private void inText(string data, string name, string str = "UTF8")
        {
            FileStream fs;
            if (Environment.OSVersion.Platform == PlatformID.Unix)
                fs = new FileStream("../../stock/" + name + ".txt", FileMode.Create);
            else
                fs = new FileStream("..\\..\\stock\\" + name + ".txt", FileMode.Create);

            //获得字节数组
            byte[] datas;
            if (str == "UTF8")
            {
                datas = Encoding.UTF8.GetBytes(data);
                fs.Write(datas, 0, data.Length);
            }
            else
            {
                datas = Encoding.Default.GetBytes(data);
                fs.Write(datas, 0, datas.Length);
            }
            //开始写入
            //清空缓冲区、关闭流
            fs.Flush();
            fs.Close();
        }

        
    }
}
