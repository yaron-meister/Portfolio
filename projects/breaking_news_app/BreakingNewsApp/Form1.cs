using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace BreakingNewsApp
{
    public partial class MainForm : Form
    {
        const int PASSWORD_MAX_LENGTH = 10;

        List<Panel> panels = new List<Panel>();
        private int currentIdx = 0;
        private NewsServer newsServer = new NewsServer();
        private NewsServer.News updatedNews = new NewsServer.News();
        string appMembersFile = @"app_members.txt";

        public MainForm()
        {
            InitializeComponent();

            if (!File.Exists(appMembersFile))
            {
                File.Create(appMembersFile);
            }

            updatedNews.status = "Fail";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private async void Refresh_Click(object sender, EventArgs e)
        {
            await RefreshNews();
        }

        private async Task RefreshNews()
        {
            updatedNews = await newsServer.GetNews();
            currentIdx = 0;
            RefreshMainForm();
        }

        private void RefreshMainForm()
        {
            if ("Fail" != updatedNews.status)
            {
                Headline.Text = updatedNews.articles[currentIdx].title;
                Content.Text = updatedNews.articles[currentIdx].content;
                Index.Text = ((currentIdx + 1) + " / " + updatedNews.articles.Count);
            }
            else
            {
                Headline.Text = "Connection Error";
                Content.Text = "Check your connection";
            }
        }


        private void ToggleNext_Click(object sender, EventArgs e)
        {
            ++currentIdx;

            if (currentIdx >= updatedNews.articles.Count)
            {
                currentIdx = 0;
            }

            RefreshMainForm();
        }

        private void TogglePrev_Click(object sender, EventArgs e)
        {
            --currentIdx;

            if (currentIdx < 0)
            {
                currentIdx = updatedNews.articles.Count - 1;
            }

            RefreshMainForm();
        }

        private void ToggleEnd_Click(object sender, EventArgs e)
        {
            currentIdx = updatedNews.articles.Count - 1;
            RefreshMainForm();
        }

        private void ToggleStart_Click(object sender, EventArgs e)
        {
            currentIdx = 0;
            RefreshMainForm();
        }

        private void signMeUpButton_Click(object sender, EventArgs e)
        {
            signInPanel.Hide();
            signUpPanel.Show();
        }

        private void signUpButton_Click(object sender, EventArgs e)
        {
            if ("" != upUsernameText.Text)
            {
                if (upPasswordText.Text.Length > PASSWORD_MAX_LENGTH)
                {
                    upErrorLabel.Text = "Password include up to 10 charachters";
                }
                else
                {
                    if (reenterPasswordText.Text == upPasswordText.Text)
                    {
                        if (upPasswordText.Text.Contains(','))
                        {
                            upErrorLabel.Text = "A comma (',') is not valid for using in password";
                        }
                        else
                        {
                            try
                            {
                                bool isUsernameExist = false;

                                using (StreamReader streamReader = File.OpenText(appMembersFile))
                                {
                                    string line = "";

                                    while (null != (line = streamReader.ReadLine()) && !isUsernameExist)
                                    {
                                        isUsernameExist = (line.Contains(upUsernameText.Text));
                                    }
                                }
                        
                                if (isUsernameExist)
                                {
                                    upErrorLabel.Text = "Username already exist";
                                }
                                else
                                {
                                    using (StreamWriter streamWriter = File.AppendText(appMembersFile))
                                    {
                                        streamWriter.WriteLine(upUsernameText.Text + "," + upPasswordText.Text);
                                        upErrorLabel.Text = "";
                                        signUpPanel.Hide();
                                        newsPanel.Show();
                                    }
                                }
                            }
                            catch (Exception exception)
                            {
                                Console.WriteLine("Exception while trying to handle 'app_members.txt'");
                                Console.WriteLine("Exception details: " + exception);
                            }
                        }
                    }
                    else
                    {
                        upErrorLabel.Text = "Passwords are not the same";
                    }
                }
            }
        }

        private async void signInButton_Click(object sender, EventArgs e)
        {
            using (StreamReader streamReader = File.OpenText(appMembersFile))
            {
                string line = "";
                string[] seperator = { "," };
                bool isUserValid = false;

                while (null != (line = streamReader.ReadLine()) && !isUserValid)
                {
                    string[] splittedList = line.Split(seperator, StringSplitOptions.RemoveEmptyEntries);

                    isUserValid = (inUsernameText.Text == splittedList[0] && inPasswordText.Text == splittedList[1]);
                }

                if (isUserValid)
                {
                    signInPanel.Hide();
                    signUpPanel.Hide();
                    newsPanel.Show();

                    await RefreshNews();                 }
                else
                {
                    inErrorLabel.Text = "Username or Password not valid";
                }
            }
        }

        private void Disconnect_Click(object sender, EventArgs e)
        {
            inUsernameText.Text = "";
            inPasswordText.Text = "";
            newsPanel.Hide();
            signUpPanel.Hide();
            signInPanel.Show();
        }
    }
}
