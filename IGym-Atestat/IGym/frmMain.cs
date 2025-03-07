using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;
using System.Net;
using System.Net.Mail;

namespace Gestiune_sala_crossfit
{
    public partial class frmMain : Form
    {
        antrenor[] antrenori = new antrenor[100];
        eveniment[] evenimente = new eveniment[100];
        int nra = 0, oka = 0, nre = 0, oke = 0;
        public frmMain()
        {
            InitializeComponent();
        }
        public static frmConectare conect;

        private void btncon_Click(object sender, EventArgs e)
        {
            if (conect == null)
            {
                conect = new frmConectare();
                conect.Show();
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (panel1.Visible == true)
            {
                panel1.Visible = false;
                panel2.Visible = true;
            }
            else
            {
                if (panel2.Visible == true)
                {
                    panel2.Visible = false;
                    panel3.Visible = true;
                }
                else
                {
                    panel3.Visible = false;
                    panel1.Visible = true;
                }

            }
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            lblhome.Font = new Font("Arial Rounded MT", 18, FontStyle.Italic);
            lblevent.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblcontact.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblechipa.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            timer1.Start();
        }



        private void lblhome_MouseHover(object sender, EventArgs e)
        {

        }


        //------------Detalii---------
        #region Detalii       
        private void lbldetalii_MouseHover(object sender, EventArgs e)
        {
            lbldetalii.BackColor = Color.White;
            lbldetalii.ForeColor = Color.FromArgb(17, 35, 45);
        }

        private void lbldetalii_MouseLeave(object sender, EventArgs e)
        {
            lbldetalii.ForeColor = Color.White;
            lbldetalii.BackColor = Color.FromArgb(17, 35, 45);
        }

        private void lblnoi_MouseHover(object sender, EventArgs e)
        {
            lblnoi.BackColor = Color.White;
            lblnoi.ForeColor = Color.FromArgb(17, 35, 45);
        }

        private void lblnoi_MouseLeave(object sender, EventArgs e)
        {
            lblnoi.ForeColor = Color.White;
            lblnoi.BackColor = Color.FromArgb(17, 35, 45);
        }
        private void lbldetalii_Click(object sender, EventArgs e)
        {
            pnlcross.Visible = true;
            pnlnoi.Visible = false;
            pnlcross.BringToFront();
        }

        private void lblnoi_Click(object sender, EventArgs e)
        {
            pnlnoi.Visible = true;
            pnlcross.Visible = false;
            pnlnoi.BringToFront();
        }

        private void exitnoi_Click(object sender, EventArgs e)
        {
            pnlnoi.Visible = false;
        }


        private void exitcross_Click(object sender, EventArgs e)
        {
            pnlcross.Visible = false;
        }
        #endregion
        //............................
        //------------Contact--------
        #region contact
        private void lblcontact_Click(object sender, EventArgs e)
        {
            lblhome.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblevent.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblcontact.Font = new Font("Arial Rounded MT", 18, FontStyle.Italic);
            lblechipa.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            pnlcontact.Visible = true;
            pnlhome.Visible = false;
            pnlechipa.Visible = false;
            pnlevent.Visible = false;
        }
        #endregion
        //..........................
        //-------------Home--------
        #region home
        private void lblhome_Click(object sender, EventArgs e)
        {
            lblhome.Font = new Font("Arial Rounded MT", 18,FontStyle.Italic );
            lblevent.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblcontact.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblechipa.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            pnlhome.Visible = true;
            pnlcontact.Visible = false;
            pnlechipa.Visible = false;
            pnlevent.Visible = false;
        }
            private bool IsValidAddress(string mail)
            {
                try
                {
                    MailAddress address = new MailAddress(mail);
                    return address.Address == mail;
            }
                catch
                {
                    return false;
                }
            }
        private void button1_Click(object sender, EventArgs e)
        {
            
            if(IsValidAddress(tbcemail.Text) == true && String.IsNullOrEmpty(tbcnume.Text)==false && String.IsNullOrEmpty(tbcmesaj.Text)==false)
            { 
                MailMessage mail = new MailMessage();
                mail.From = new MailAddress("igymromania@gmail.com");
                mail.To.Add("igymromania@gmail.com");
                mail.Subject = tbcnume.Text;
                mail.Body = "Email: " + tbcemail.Text + "\n\n" + tbcmesaj.Text;

                SmtpClient server = new SmtpClient("smtp.gmail.com");
                server.Port = 587;
                server.UseDefaultCredentials = false;
                server.Credentials = new NetworkCredential("igymromania@gmail.com", "dzze yard bwmq qkax");
                server.EnableSsl = true;

                try { 
                    server.Send(mail);
                    MessageBox.Show("Mesaj trimis cu succes", "Contact", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch(Exception ex)
                {
                    MessageBox.Show("Eroare la trimitere!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            else
            {

            }
        }

        
        #endregion
        //...................
        //--------------Echipa--------
        #region echipa
        private void lblechipa_Click(object sender, EventArgs e)
        {
            lblhome.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblevent.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblcontact.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblechipa.Font = new Font("Arial Rounded MT", 18, FontStyle.Italic);
            nra = 0;
            try
            {
                //creare conexiune
                MySqlConnection connection = new MySqlConnection();
                connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                connection.Open();

                //creare comanda   
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;
                cmd.CommandText = @"Select * from antrenori";

                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                while (r.Read())
                {
                    antrenori[nra] = new antrenor();
                    antrenori[nra].nume = r["nume"].ToString();
                    antrenori[nra].desc = r["descriere"].ToString();
                    antrenori[nra].spec = r["spec"].ToString();
                    antrenori[nra].id = int.Parse(r["ida"].ToString());
                    antrenori[nra].varsta = DateTime.Parse(r["varsta"].ToString());
                    antrenori[nra].cale = r["cale"].ToString();
                    nra++;
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            pnlant.Controls.Clear();

            for (int i = 0; i < nra; i++)
            {
                oka = 1;
                PictureBox pb = new PictureBox();
                pb.Parent = pnlant;
                pb.Location = new Point(15, i * 180 + (i + 1) * 15);
                pb.Size = new Size(250, 180);
                pb.SizeMode = PictureBoxSizeMode.StretchImage;
                pb.ImageLocation = AppDomain.CurrentDomain.BaseDirectory + antrenori[i].cale;
                pb.Click += pb_click;
                pb.Tag = i;
                pb.BorderStyle = BorderStyle.FixedSingle;
            }


            pnlechipa.Visible = true;
            pnlhome.Visible = false;
            pnlcontact.Visible = false;
            pnlevent.Visible = false;

            antrenor a = antrenori[0];
            pnldesc.Controls.Clear();
            Label lbl = new Label();
            #region nume
            lbl.Text = a.nume;
            lbl.Parent = pnldesc;
            lbl.Location = new Point(0, 0);
            lbl.Size = new Size(725, 60);
            lbl.Font = new Font("Algeric", 30, FontStyle.Bold);
            lbl.ForeColor = Color.White;
            lbl.TextAlign = ContentAlignment.MiddleCenter;
            #endregion
            Label lbl2 = new Label();
            #region specializare + varsta
            lbl2.Text = "Specializare: " + a.spec + "\n" + "Varsta: " + (DateTime.Now.Year - a.varsta.Year).ToString() + " ani";
            lbl2.Parent = pnldesc;
            lbl2.Location = new Point(10, 65);
            lbl2.AutoSize = true;
            lbl2.Font = new Font("Algeric", 20);
            lbl2.ForeColor = Color.White;
            #endregion
            Label lbl3 = new Label();
            #region descriere
            lbl3.Text = a.desc;
            lbl3.Parent = pnldesc;
            lbl3.Location = new Point(10, 140);
            lbl3.Size = new Size(700, 500);
            lbl3.AutoSize = false;
            lbl3.Font = new Font("Algeric", 15);
            lbl3.ForeColor = Color.White;
            #endregion
        }


        private void pb_click(object sender, EventArgs e)
        {
            PictureBox pb = sender as PictureBox;
            antrenor a = antrenori[int.Parse(pb.Tag.ToString())];
            pnldesc.Controls.Clear();
            Label lbl = new Label();
            #region nume
            lbl.Text = a.nume;
            lbl.Parent = pnldesc;
            lbl.Location = new Point(0, 0);
            lbl.Size = new Size(725, 60);
            lbl.Font = new Font("Algeric", 30, FontStyle.Bold);
            lbl.ForeColor = Color.White;
            lbl.TextAlign = ContentAlignment.MiddleCenter;
            #endregion
            Label lbl2 = new Label();
            #region specializare + varsta
            lbl2.Text = "Specializare: " + a.spec + "\n" + "Varsta: " + (DateTime.Now.Year-a.varsta.Year).ToString() + " ani";
            lbl2.Parent = pnldesc;
            lbl2.Location = new Point(10, 65);
            lbl2.AutoSize = true;
            lbl2.Font = new Font("Algeric", 20);
            lbl2.ForeColor = Color.White;
            #endregion
            Label lbl3 = new Label();
            #region descriere
          
            lbl3.Text = a.desc;
            lbl3.Parent = pnldesc;
            lbl3.Location = new Point(10, 140);
            lbl3.Size = new Size(700, 500);
            lbl3.AutoSize = false;
            lbl3.Font = new Font("Algeric", 15);
            lbl3.ForeColor = Color.White;
            #endregion
        }
        #endregion
        //.....................
        //----------Eveniment
        #region eveniment
        private void lblevent_Click(object sender, EventArgs e)
        {
            lblhome.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblevent.Font = new Font("Arial Rounded MT", 18, FontStyle.Italic);
            lblcontact.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            lblechipa.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
            nre = 0;
            try
            {
                //creare conexiune
                MySqlConnection connection = new MySqlConnection();
                connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                connection.Open();

                //creare comanda   
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;
                cmd.CommandText = @"Select * from evenimente";

                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                while (r.Read())
                {
                    evenimente[nre] = new eveniment();
                    evenimente[nre].nume = r["nume"].ToString();
                    evenimente[nre].data = (DateTime?)r["data"];
                    evenimente[nre].desc = r["descriere"].ToString();
                    evenimente[nre].cale = r["cale"].ToString();
                    nre++;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            pnle.Controls.Clear(); 
            for (int i = 0; i < nre; i++)
            {
                Panel pnl = new Panel();
                #region panel
                pnl.Parent = pnle;
                pnl.BackColor = Color.White;
                pnl.Location = new Point(50, 10 * (i + 1) + 200 * i);
                pnl.Size = new Size(1000, 200);
                pnl.BackColor = Color.FromArgb(120,120,120);
                #endregion
                PictureBox pb = new PictureBox();
                #region imagine
                pb.Parent = pnl;
                pb.Size = new Size(250, 180);
                pb.Location = new Point(10, 10);
                pb.ImageLocation = AppDomain.CurrentDomain.BaseDirectory + evenimente[i].cale;
                pb.SizeMode = PictureBoxSizeMode.StretchImage;
                pb.BorderStyle = BorderStyle.FixedSingle;
                #endregion
                Label lbl = new Label();
                #region nume
                lbl.Parent = pnl;
                lbl.Location = new Point(270,10);
                lbl.Font = new Font("Arial Rounded MT", 20, FontStyle.Bold);
                lbl.Text = evenimente[i].nume + "     " + evenimente[i].data;
                lbl.AutoSize = true;
                #endregion
                Label lbl2 = new Label();
                #region descriere
                lbl2.Parent = pnl;
                lbl2.Location = new Point(280, 50);
                lbl2.Text = evenimente[i].desc;
                lbl2.Font = new Font("Arial Rounded MT", 11, FontStyle.Bold);
                lbl2.AutoSize = true;
                #endregion

            }
            pnlevent.Visible = true;
            pnlechipa.Visible = false;
            pnlhome.Visible = false;
            pnlcontact.Visible = false;
        }
        #endregion
        //.....................
    }
}
