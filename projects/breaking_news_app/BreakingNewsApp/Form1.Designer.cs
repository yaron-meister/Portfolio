using System.Threading.Tasks;

namespace BreakingNewsApp
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.panelLeft = new System.Windows.Forms.Panel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.signInPanel = new System.Windows.Forms.Panel();
            this.signInButton = new System.Windows.Forms.Button();
            this.inErrorLabel = new System.Windows.Forms.Label();
            this.signInLabel = new System.Windows.Forms.Label();
            this.signMeUpButton = new System.Windows.Forms.Button();
            this.inUsernameLabel = new System.Windows.Forms.Label();
            this.inUsernameText = new System.Windows.Forms.TextBox();
            this.inPasswordLabel = new System.Windows.Forms.Label();
            this.inPasswordText = new System.Windows.Forms.TextBox();
            this.notRegisteredLabel = new System.Windows.Forms.Label();
            this.signUpPanel = new System.Windows.Forms.Panel();
            this.upErrorLabel = new System.Windows.Forms.Label();
            this.signUpLabel = new System.Windows.Forms.Label();
            this.upUsernameLabel = new System.Windows.Forms.Label();
            this.upUsernameText = new System.Windows.Forms.TextBox();
            this.reenterPasswordLabel = new System.Windows.Forms.Label();
            this.upPasswordLabel = new System.Windows.Forms.Label();
            this.signUpButton = new System.Windows.Forms.Button();
            this.reenterPasswordText = new System.Windows.Forms.TextBox();
            this.upPasswordText = new System.Windows.Forms.TextBox();
            this.newsPanel = new System.Windows.Forms.Panel();
            this.Disconnect = new System.Windows.Forms.Button();
            this.Index = new System.Windows.Forms.Label();
            this.Refresh = new System.Windows.Forms.Button();
            this.ToggleEnd = new System.Windows.Forms.Button();
            this.ToggleNext = new System.Windows.Forms.Button();
            this.TogglePrev = new System.Windows.Forms.Button();
            this.ToggleStart = new System.Windows.Forms.Button();
            this.Content = new System.Windows.Forms.Label();
            this.Headline = new System.Windows.Forms.Label();
            this.alreadySigned = new System.Windows.Forms.Label();
            this.panelLeft.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.signInPanel.SuspendLayout();
            this.signUpPanel.SuspendLayout();
            this.newsPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelLeft
            // 
            this.panelLeft.Controls.Add(this.pictureBox1);
            this.panelLeft.Dock = System.Windows.Forms.DockStyle.Left;
            this.panelLeft.Location = new System.Drawing.Point(0, 0);
            this.panelLeft.Name = "panelLeft";
            this.panelLeft.Size = new System.Drawing.Size(400, 760);
            this.panelLeft.TabIndex = 0;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(400, 760);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // signInPanel
            // 
            this.signInPanel.Controls.Add(this.signInButton);
            this.signInPanel.Controls.Add(this.inErrorLabel);
            this.signInPanel.Controls.Add(this.signInLabel);
            this.signInPanel.Controls.Add(this.signMeUpButton);
            this.signInPanel.Controls.Add(this.inUsernameLabel);
            this.signInPanel.Controls.Add(this.inUsernameText);
            this.signInPanel.Controls.Add(this.inPasswordLabel);
            this.signInPanel.Controls.Add(this.inPasswordText);
            this.signInPanel.Controls.Add(this.notRegisteredLabel);
            this.signInPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.signInPanel.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.signInPanel.Location = new System.Drawing.Point(400, 0);
            this.signInPanel.Name = "signInPanel";
            this.signInPanel.Size = new System.Drawing.Size(747, 760);
            this.signInPanel.TabIndex = 1;
            // 
            // signInButton
            // 
            this.signInButton.BackColor = System.Drawing.Color.MediumSeaGreen;
            this.signInButton.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.signInButton.Location = new System.Drawing.Point(158, 384);
            this.signInButton.Name = "signInButton";
            this.signInButton.Size = new System.Drawing.Size(112, 34);
            this.signInButton.TabIndex = 6;
            this.signInButton.Text = "Sign In";
            this.signInButton.UseVisualStyleBackColor = false;
            this.signInButton.Click += new System.EventHandler(this.signInButton_Click);
            // 
            // inErrorLabel
            // 
            this.inErrorLabel.AutoSize = true;
            this.inErrorLabel.ForeColor = System.Drawing.Color.Red;
            this.inErrorLabel.Location = new System.Drawing.Point(158, 345);
            this.inErrorLabel.Name = "inErrorLabel";
            this.inErrorLabel.Size = new System.Drawing.Size(0, 25);
            this.inErrorLabel.TabIndex = 5;
            // 
            // signInLabel
            // 
            this.signInLabel.AutoSize = true;
            this.signInLabel.Font = new System.Drawing.Font("Century Gothic", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.signInLabel.ForeColor = System.Drawing.Color.MediumSeaGreen;
            this.signInLabel.Location = new System.Drawing.Point(158, 80);
            this.signInLabel.Name = "signInLabel";
            this.signInLabel.Size = new System.Drawing.Size(135, 43);
            this.signInLabel.TabIndex = 0;
            this.signInLabel.Text = "Sign In";
            // 
            // signMeUpButton
            // 
            this.signMeUpButton.Location = new System.Drawing.Point(341, 469);
            this.signMeUpButton.Name = "signMeUpButton";
            this.signMeUpButton.Size = new System.Drawing.Size(165, 34);
            this.signMeUpButton.TabIndex = 4;
            this.signMeUpButton.Text = "Sign Me Up";
            this.signMeUpButton.UseVisualStyleBackColor = true;
            this.signMeUpButton.Click += new System.EventHandler(this.signMeUpButton_Click);
            // 
            // inUsernameLabel
            // 
            this.inUsernameLabel.AutoSize = true;
            this.inUsernameLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.inUsernameLabel.ForeColor = System.Drawing.Color.MediumSeaGreen;
            this.inUsernameLabel.Location = new System.Drawing.Point(158, 163);
            this.inUsernameLabel.Name = "inUsernameLabel";
            this.inUsernameLabel.Size = new System.Drawing.Size(140, 30);
            this.inUsernameLabel.TabIndex = 0;
            this.inUsernameLabel.Text = "Username:";
            // 
            // inUsernameText
            // 
            this.inUsernameText.Location = new System.Drawing.Point(158, 196);
            this.inUsernameText.Name = "inUsernameText";
            this.inUsernameText.Size = new System.Drawing.Size(317, 31);
            this.inUsernameText.TabIndex = 1;
            // 
            // inPasswordLabel
            // 
            this.inPasswordLabel.AutoSize = true;
            this.inPasswordLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.inPasswordLabel.ForeColor = System.Drawing.Color.MediumSeaGreen;
            this.inPasswordLabel.Location = new System.Drawing.Point(158, 258);
            this.inPasswordLabel.Name = "inPasswordLabel";
            this.inPasswordLabel.Size = new System.Drawing.Size(129, 30);
            this.inPasswordLabel.TabIndex = 0;
            this.inPasswordLabel.Text = "Password:";
            // 
            // inPasswordText
            // 
            this.inPasswordText.Location = new System.Drawing.Point(158, 291);
            this.inPasswordText.Name = "inPasswordText";
            this.inPasswordText.Size = new System.Drawing.Size(317, 31);
            this.inPasswordText.TabIndex = 1;
            this.inPasswordText.UseSystemPasswordChar = true;
            // 
            // notRegisteredLabel
            // 
            this.notRegisteredLabel.AutoSize = true;
            this.notRegisteredLabel.Location = new System.Drawing.Point(158, 474);
            this.notRegisteredLabel.Name = "notRegisteredLabel";
            this.notRegisteredLabel.Size = new System.Drawing.Size(148, 25);
            this.notRegisteredLabel.TabIndex = 3;
            this.notRegisteredLabel.Text = "Not Registered?";
            // 
            // signUpPanel
            // 
            this.signUpPanel.Controls.Add(this.alreadySigned);
            this.signUpPanel.Controls.Add(this.upErrorLabel);
            this.signUpPanel.Controls.Add(this.signUpLabel);
            this.signUpPanel.Controls.Add(this.upUsernameLabel);
            this.signUpPanel.Controls.Add(this.upUsernameText);
            this.signUpPanel.Controls.Add(this.reenterPasswordLabel);
            this.signUpPanel.Controls.Add(this.upPasswordLabel);
            this.signUpPanel.Controls.Add(this.signUpButton);
            this.signUpPanel.Controls.Add(this.reenterPasswordText);
            this.signUpPanel.Controls.Add(this.upPasswordText);
            this.signUpPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.signUpPanel.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.signUpPanel.Location = new System.Drawing.Point(400, 0);
            this.signUpPanel.Name = "signUpPanel";
            this.signUpPanel.Size = new System.Drawing.Size(747, 760);
            this.signUpPanel.TabIndex = 1;
            // 
            // upErrorLabel
            // 
            this.upErrorLabel.AutoSize = true;
            this.upErrorLabel.ForeColor = System.Drawing.Color.Red;
            this.upErrorLabel.Location = new System.Drawing.Point(158, 430);
            this.upErrorLabel.Name = "upErrorLabel";
            this.upErrorLabel.Size = new System.Drawing.Size(0, 25);
            this.upErrorLabel.TabIndex = 5;
            // 
            // signUpLabel
            // 
            this.signUpLabel.AutoSize = true;
            this.signUpLabel.Font = new System.Drawing.Font("Century Gothic", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.signUpLabel.ForeColor = System.Drawing.Color.MediumSeaGreen;
            this.signUpLabel.Location = new System.Drawing.Point(158, 80);
            this.signUpLabel.Name = "signUpLabel";
            this.signUpLabel.Size = new System.Drawing.Size(150, 43);
            this.signUpLabel.TabIndex = 0;
            this.signUpLabel.Text = "Sign Up";
            // 
            // upUsernameLabel
            // 
            this.upUsernameLabel.AutoSize = true;
            this.upUsernameLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.upUsernameLabel.ForeColor = System.Drawing.Color.MediumSeaGreen;
            this.upUsernameLabel.Location = new System.Drawing.Point(158, 163);
            this.upUsernameLabel.Name = "upUsernameLabel";
            this.upUsernameLabel.Size = new System.Drawing.Size(140, 30);
            this.upUsernameLabel.TabIndex = 0;
            this.upUsernameLabel.Text = "Username:";
            // 
            // upUsernameText
            // 
            this.upUsernameText.Location = new System.Drawing.Point(158, 196);
            this.upUsernameText.Name = "upUsernameText";
            this.upUsernameText.Size = new System.Drawing.Size(317, 31);
            this.upUsernameText.TabIndex = 1;
            // 
            // reenterPasswordLabel
            // 
            this.reenterPasswordLabel.AutoSize = true;
            this.reenterPasswordLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.reenterPasswordLabel.ForeColor = System.Drawing.Color.MediumSeaGreen;
            this.reenterPasswordLabel.Location = new System.Drawing.Point(158, 351);
            this.reenterPasswordLabel.Name = "reenterPasswordLabel";
            this.reenterPasswordLabel.Size = new System.Drawing.Size(239, 30);
            this.reenterPasswordLabel.TabIndex = 0;
            this.reenterPasswordLabel.Text = "Re-enter password:";
            // 
            // upPasswordLabel
            // 
            this.upPasswordLabel.AutoSize = true;
            this.upPasswordLabel.Font = new System.Drawing.Font("Century Gothic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.upPasswordLabel.ForeColor = System.Drawing.Color.MediumSeaGreen;
            this.upPasswordLabel.Location = new System.Drawing.Point(158, 258);
            this.upPasswordLabel.Name = "upPasswordLabel";
            this.upPasswordLabel.Size = new System.Drawing.Size(129, 30);
            this.upPasswordLabel.TabIndex = 0;
            this.upPasswordLabel.Text = "Password:";
            // 
            // signUpButton
            // 
            this.signUpButton.BackColor = System.Drawing.Color.MediumSeaGreen;
            this.signUpButton.Font = new System.Drawing.Font("Century Gothic", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.signUpButton.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.signUpButton.Location = new System.Drawing.Point(158, 458);
            this.signUpButton.Name = "signUpButton";
            this.signUpButton.Size = new System.Drawing.Size(112, 45);
            this.signUpButton.TabIndex = 2;
            this.signUpButton.Text = "Sign Up";
            this.signUpButton.UseVisualStyleBackColor = false;
            this.signUpButton.Click += new System.EventHandler(this.signUpButton_Click);
            // 
            // reenterPasswordText
            // 
            this.reenterPasswordText.Location = new System.Drawing.Point(158, 384);
            this.reenterPasswordText.Name = "reenterPasswordText";
            this.reenterPasswordText.Size = new System.Drawing.Size(317, 31);
            this.reenterPasswordText.TabIndex = 1;
            this.reenterPasswordText.UseSystemPasswordChar = true;
            // 
            // upPasswordText
            // 
            this.upPasswordText.Location = new System.Drawing.Point(158, 291);
            this.upPasswordText.Name = "upPasswordText";
            this.upPasswordText.Size = new System.Drawing.Size(317, 31);
            this.upPasswordText.TabIndex = 1;
            this.upPasswordText.UseSystemPasswordChar = true;
            // 
            // newsPanel
            // 
            this.newsPanel.Controls.Add(this.Disconnect);
            this.newsPanel.Controls.Add(this.Index);
            this.newsPanel.Controls.Add(this.Refresh);
            this.newsPanel.Controls.Add(this.ToggleEnd);
            this.newsPanel.Controls.Add(this.ToggleNext);
            this.newsPanel.Controls.Add(this.TogglePrev);
            this.newsPanel.Controls.Add(this.ToggleStart);
            this.newsPanel.Controls.Add(this.Content);
            this.newsPanel.Controls.Add(this.Headline);
            this.newsPanel.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.newsPanel.Location = new System.Drawing.Point(400, 0);
            this.newsPanel.Name = "newsPanel";
            this.newsPanel.Size = new System.Drawing.Size(747, 760);
            this.newsPanel.TabIndex = 1;
            // 
            // Disconnect
            // 
            this.Disconnect.Location = new System.Drawing.Point(625, 0);
            this.Disconnect.Name = "Disconnect";
            this.Disconnect.Size = new System.Drawing.Size(122, 34);
            this.Disconnect.TabIndex = 5;
            this.Disconnect.Text = "Disconnect";
            this.Disconnect.UseVisualStyleBackColor = true;
            this.Disconnect.Click += new System.EventHandler(this.Disconnect_Click);
            // 
            // Index
            // 
            this.Index.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Index.Location = new System.Drawing.Point(282, 665);
            this.Index.Name = "Index";
            this.Index.Size = new System.Drawing.Size(179, 51);
            this.Index.TabIndex = 3;
            this.Index.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // Refresh
            // 
            this.Refresh.Image = ((System.Drawing.Image)(resources.GetObject("Refresh.Image")));
            this.Refresh.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.Refresh.Location = new System.Drawing.Point(0, 0);
            this.Refresh.Name = "Refresh";
            this.Refresh.Size = new System.Drawing.Size(43, 34);
            this.Refresh.TabIndex = 4;
            this.Refresh.UseVisualStyleBackColor = true;
            this.Refresh.Click += new System.EventHandler(this.Refresh_Click);
            // 
            // ToggleEnd
            // 
            this.ToggleEnd.Location = new System.Drawing.Point(590, 665);
            this.ToggleEnd.Name = "ToggleEnd";
            this.ToggleEnd.Size = new System.Drawing.Size(80, 51);
            this.ToggleEnd.TabIndex = 2;
            this.ToggleEnd.Text = ">>";
            this.ToggleEnd.UseVisualStyleBackColor = true;
            this.ToggleEnd.Click += new System.EventHandler(this.ToggleEnd_Click);
            // 
            // ToggleNext
            // 
            this.ToggleNext.Location = new System.Drawing.Point(504, 665);
            this.ToggleNext.Name = "ToggleNext";
            this.ToggleNext.Size = new System.Drawing.Size(80, 51);
            this.ToggleNext.TabIndex = 2;
            this.ToggleNext.Text = ">";
            this.ToggleNext.UseVisualStyleBackColor = true;
            this.ToggleNext.Click += new System.EventHandler(this.ToggleNext_Click);
            // 
            // TogglePrev
            // 
            this.TogglePrev.Location = new System.Drawing.Point(158, 665);
            this.TogglePrev.Name = "TogglePrev";
            this.TogglePrev.Size = new System.Drawing.Size(80, 51);
            this.TogglePrev.TabIndex = 2;
            this.TogglePrev.Text = "<";
            this.TogglePrev.UseVisualStyleBackColor = true;
            this.TogglePrev.Click += new System.EventHandler(this.TogglePrev_Click);
            // 
            // ToggleStart
            // 
            this.ToggleStart.Location = new System.Drawing.Point(72, 665);
            this.ToggleStart.Name = "ToggleStart";
            this.ToggleStart.Size = new System.Drawing.Size(80, 51);
            this.ToggleStart.TabIndex = 2;
            this.ToggleStart.Text = "<<";
            this.ToggleStart.UseVisualStyleBackColor = true;
            this.ToggleStart.Click += new System.EventHandler(this.ToggleStart_Click);
            // 
            // Content
            // 
            this.Content.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Content.Location = new System.Drawing.Point(72, 225);
            this.Content.Name = "Content";
            this.Content.Size = new System.Drawing.Size(598, 424);
            this.Content.TabIndex = 1;
            // 
            // Headline
            // 
            this.Headline.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.Headline.Font = new System.Drawing.Font("Times New Roman", 20F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.Headline.Location = new System.Drawing.Point(72, 42);
            this.Headline.Name = "Headline";
            this.Headline.Size = new System.Drawing.Size(598, 159);
            this.Headline.TabIndex = 0;
            this.Headline.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // alreadySigned
            // 
            this.alreadySigned.AutoSize = true;
            this.alreadySigned.Location = new System.Drawing.Point(155, 515);
            this.alreadySigned.Name = "alreadySigned";
            this.alreadySigned.Size = new System.Drawing.Size(189, 25);
            this.alreadySigned.TabIndex = 6;
            this.alreadySigned.Text = "I\'m already registered";
            this.alreadySigned.Click += new System.EventHandler(this.alreadySigned_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1147, 760);
            this.Controls.Add(this.signInPanel);
            this.Controls.Add(this.signUpPanel);
            this.Controls.Add(this.newsPanel);
            this.Controls.Add(this.panelLeft);
            this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "MainForm";
            this.Text = "BreakingNews";
            this.panelLeft.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.signInPanel.ResumeLayout(false);
            this.signInPanel.PerformLayout();
            this.signUpPanel.ResumeLayout(false);
            this.signUpPanel.PerformLayout();
            this.newsPanel.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        public async Task InitializeAsync()
        {
            signInPanel.BringToFront();
            newsPanel.SendToBack();
        }

        private System.Windows.Forms.Panel panelLeft;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Panel newsPanel;
        private System.Windows.Forms.Label Headline;
        private System.Windows.Forms.Label Content;
        private System.Windows.Forms.Button ToggleEnd;
        private System.Windows.Forms.Button ToggleNext;
        private System.Windows.Forms.Button TogglePrev;
        private System.Windows.Forms.Button ToggleStart;
        private System.Windows.Forms.Label Index;

        private System.Windows.Forms.Panel signInPanel;
        private System.Windows.Forms.Label signInLabel;
        private System.Windows.Forms.Label inUsernameLabel;
        private System.Windows.Forms.TextBox inUsernameText;
        private System.Windows.Forms.Label inPasswordLabel;
        private System.Windows.Forms.TextBox inPasswordText;
        private System.Windows.Forms.Label notRegisteredLabel;
        private System.Windows.Forms.Button signMeUpButton;
        private System.Windows.Forms.Label inErrorLabel;
        private System.Windows.Forms.Panel signUpPanel;
        private System.Windows.Forms.Label upErrorLabel;
        private System.Windows.Forms.Label signUpLabel;
        private System.Windows.Forms.Label upUsernameLabel;
        private System.Windows.Forms.TextBox upUsernameText;
        private System.Windows.Forms.Label upPasswordLabel;
        private System.Windows.Forms.Button signUpButton;
        private System.Windows.Forms.TextBox upPasswordText;
        private System.Windows.Forms.Label reenterPasswordLabel;
        private System.Windows.Forms.TextBox reenterPasswordText;
        private System.Windows.Forms.Button signInButton;
        private System.Windows.Forms.Button Refresh;
        private System.Windows.Forms.Button Disconnect;
        private System.Windows.Forms.Label alreadySigned;
    }
}

