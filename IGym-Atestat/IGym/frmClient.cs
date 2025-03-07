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
    public partial class frmClient : Form
    {
        public static frmCont cont;
        abonament[] abonamente = new abonament[100];
        eveniment[] evenimente = new eveniment[100];
        int nrab,nre=0;
        public frmClient()
        {
            InitializeComponent();
        }
        private void frmClient_Load(object sender, EventArgs e)
        {
            pnlrez.Parent = this;
            pnlrez.Location = new Point(0, 0);
        }

        private void btncont_Click(object sender, EventArgs e)
        {
            cont = new frmCont();
            cont.Show();
        }
        //------Abonamente----
        #region abonamente
        private void pbab_Click(object sender, EventArgs e)
        {
            pnlevent.Visible = false;
            pnlmain.Visible = false;
            pnlab.Visible = true;

            nrab = 0;
            try
            {
                //creare conexiune
                MySqlConnection connection = new MySqlConnection();
                connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                connection.Open();

                //creare comanda   
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;
                cmd.CommandText = @"Select * from abonamente";

                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                while (r.Read())
                {
                    abonamente[nrab] = new abonament();
                    abonamente[nrab].nume = r["nume"].ToString();
                    abonamente[nrab].desc = r["descriere"].ToString();
                    abonamente[nrab].tip = r["tip"].ToString();
                    abonamente[nrab].pret = int.Parse(r["pret"].ToString());
                    abonamente[nrab].id = int.Parse(r["idab"].ToString());
                    nrab++;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            pnlrezab.Controls.Clear();
            for(int i = 0; i < nrab; i++)
            {
                Panel pnl = new Panel();
                #region panel
                pnl.Parent = pnlrezab;
                pnl.BackColor = Color.White;
                pnl.Location = new Point(20, 10 * (i + 1) + 150 * i);
                pnl.Size = new Size(940, 150);
                pnl.BackColor = Color.FromArgb(120, 120, 120);
                #endregion
                PictureBox pb = new PictureBox();
                #region imagine
                pb.Parent = pnl;
                pb.Size = new Size(200, 130);
                pb.Location = new Point(10, 10);
                if(abonamente[i].tip == "grup")
                {
                    pb.ImageLocation = AppDomain.CurrentDomain.BaseDirectory + "\\Poze\\antrenament_grup.png";
                }
                else
                {
                    pb.ImageLocation = AppDomain.CurrentDomain.BaseDirectory + "\\Poze\\antrenament_individual.jpg";
                }
                pb.SizeMode = PictureBoxSizeMode.StretchImage;
                pb.BorderStyle = BorderStyle.FixedSingle;
                #endregion
                Button btn = new Button();
                #region buton
                btn.Parent = pnl;
                btn.Location = new Point(880, 10);
                btn.Size = new Size(50, 50);
                btn.FlatStyle = FlatStyle.Flat;
                btn.Click += btn_Click;
                btn.Tag = i;
                btn.BackgroundImage = ((System.Drawing.Image)(IGym.Properties.Resources.butonad));
                btn.BackgroundImageLayout = ImageLayout.Stretch;      
                #endregion
                Label lbl = new Label();
                #region nume
                lbl.Parent = pnl;
                lbl.Location = new Point(230, 10);
                lbl.Font = new Font("Arial Rounded MT", 18, FontStyle.Bold);
                if(abonamente[i].tip == "grup")
                {
                    lbl.Text = abonamente[i].nume + "  -  Antrenamente in grup";
                }
                else
                {
                    lbl.Text = abonamente[i].nume + "  -  Antrenamente individuale";
                }
                lbl.AutoSize = true;
                #endregion
                Label lbl3 = new Label();
                #region pret
                lbl3.Parent = pnl;
                lbl3.Location = new Point(230, 40);
                lbl3.Font = new Font("Arial Rounded MT", 16, FontStyle.Bold);
                lbl3.Text = "Pret: " + abonamente[i].pret.ToString()+ " lei/luna";
                lbl3.AutoSize = true;
                #endregion
                Label lbl2 = new Label();
                #region descriere
                lbl2.Parent = pnl;
                lbl2.Location = new Point(230, 70);
                lbl2.Text = abonamente[i].desc;
                lbl2.Font = new Font("Arial Rounded MT", 11, FontStyle.Bold);
                lbl2.AutoSize = true;
                #endregion
            }
        }
        private void btn_Click(object sender, EventArgs e)
        {
            bool adauga = true;

            try
            {
                //creare conexiune
                MySqlConnection connection = new MySqlConnection();
                connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                connection.Open();

                //creare comanda   
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;
                cmd.CommandText = @"Select * from rezabonamente where idc = @idc and idab = @idab";

                cmd.Parameters.AddWithValue("idc", client.id);
                cmd.Parameters.AddWithValue("idab", abonamente[int.Parse((sender as Button).Tag.ToString())].id);
                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                if (r.Read())
                {
                    adauga = false;
                }
            }
            catch
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            if (adauga)
            {
                try
                {
                    //creare conexiune
                    MySqlConnection connection = new MySqlConnection();
                    connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                    connection.Open();

                    //creare comanda   
                    MySqlCommand cmd = new MySqlCommand();
                    cmd.Connection = connection;
                    cmd.CommandText = @"INSERT INTO rezabonamente(idc,idab) VALUES(@idc,@idab);";

                    //stabilirea parametrilor 
                    cmd.Parameters.AddWithValue("idc", client.id);
                    cmd.Parameters.AddWithValue("idab", abonamente[int.Parse((sender as Button).Tag.ToString())].id);
                    //verificare
                    if (cmd.ExecuteNonQuery() != 0)
                    {
                        MailMessage mail = new MailMessage();
                        mail.From = new MailAddress("igymromania@gmail.com");
                        mail.To.Add(client.email);
                        mail.Subject = "Rezervare facuta cu succes";
                        mail.Body = "Ati rezervat cu succes abonamentul: " + abonamente[int.Parse((sender as Button).Tag.ToString())].nume + '\n' + "Pretul este de: " + abonamente[int.Parse((sender as Button).Tag.ToString())].pret + " lei/luna." + '\n' +'\n' + '\n'+ "IGym \nAdresa: Iaşi, Strada Petre Andrei 9, Iaşi 700496\nTelefon: 0771 518 956";

                        SmtpClient server = new SmtpClient("smtp.gmail.com");
                        server.Port = 587;
                        server.UseDefaultCredentials = false;
                        server.Credentials = new NetworkCredential("igymromania@gmail.com", "dzze yard bwmq qkax");
                        server.EnableSsl = true;

                        server.Send(mail);

                        MessageBox.Show("Abonament rezervat cu succes!", "Rezervare abonament", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                   else
                    {
                        MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            else
            {
                MessageBox.Show("Aveti deja rezervare facuta pentru acest abonament!", "Rezervare abonament", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
        #endregion
        //-------------
        //-----Evenimente
        #region evenimente
        private void pbevent_Click(object sender, EventArgs e)
        {
            pnlevent.Visible = true;
            pnlmain.Visible = false;
            pnlab.Visible = false;
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
                    evenimente[nre].cale = r["cale"].ToString();
                    evenimente[nre].pret = int.Parse(r["pret"].ToString());
                    evenimente[nre].id = int.Parse(r["ide"].ToString());
                    nre++;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            pnlev.Controls.Clear();
            for (int i = 0; i < nre; i++)
            {
                Panel pnl = new Panel();
                #region panel
                pnl.Parent = pnlev;
                pnl.BackColor = Color.White;
                pnl.Location = new Point(20*(i+1)+300*i, 30);
                pnl.Size = new Size(300, 450);
                pnl.BackColor = Color.FromArgb(120, 120, 120);
                #endregion
                PictureBox pb = new PictureBox();
                #region imagine
                pb.Parent = pnl;
                pb.Size = new Size(270, 200);
                pb.Location = new Point(15, 150);
                pb.ImageLocation = AppDomain.CurrentDomain.BaseDirectory + evenimente[i].cale;
                pb.SizeMode = PictureBoxSizeMode.StretchImage;
                pb.BorderStyle = BorderStyle.FixedSingle;
                #endregion
                Label lbl = new Label();
                #region nume
                lbl.Parent = pnl;
                lbl.Location = new Point(15, 10);
                lbl.Font = new Font("Arial Rounded MT", 22, FontStyle.Bold);
                lbl.Text = evenimente[i].nume;
                lbl.AutoSize = false;
                lbl.TextAlign = ContentAlignment.MiddleCenter;
                lbl.Size = new Size(280,100);
                #endregion
                Label lbl2 = new Label();
                #region pret
                lbl2.Parent = pnl;
                lbl2.Location = new Point(15, 110);
                lbl2.Text = "Pret intrare: " + evenimente[i].pret.ToString()+ " lei";
                lbl2.Font = new Font("Arial Rounded MT", 15, FontStyle.Bold);
                lbl2.TextAlign = ContentAlignment.MiddleCenter;
                lbl2.AutoSize = false;
                lbl2.Size = new Size(280, 20);
                #endregion
                Button btn = new Button();
                #region buton
                btn.Parent = pnl;
                btn.Location = new Point(15, 370);
                btn.Size = new Size(270, 60);
                btn.Click += btn_Click2;
                btn.Text = "Rezerva acum";
                btn.Font = new Font("Arial Rounded MT", 20, FontStyle.Bold);
                btn.ForeColor = Color.White;
                btn.BackColor = Color.FromArgb(17,35,45);
                btn.Tag = i;
                #endregion

            }

        }
        private void btn_Click2(object sender, EventArgs e)
        {
            bool adauga = true;
            try
            {
                //creare conexiune
                MySqlConnection connection = new MySqlConnection();
                connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                connection.Open();

                //creare comanda   
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;
                cmd.CommandText = @"Select * from rezevenimente where idc = @idc and ide = @ide";

                cmd.Parameters.AddWithValue("idc", client.id);
                cmd.Parameters.AddWithValue("ide", evenimente[int.Parse((sender as Button).Tag.ToString())].id);
                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                if (r.Read())
                {
                    adauga = false;
                }
            }
            catch
            {

            }
            if (adauga)
            {
                try
                {
                    //creare conexiune
                    MySqlConnection connection = new MySqlConnection();
                    connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                    connection.Open();

                    //creare comanda   
                    MySqlCommand cmd = new MySqlCommand();
                    cmd.Connection = connection;
                    cmd.CommandText = @"INSERT INTO rezevenimente(idc,ide) VALUES(@idc,@ide);";

                    //stabilirea parametrilor 
                    cmd.Parameters.AddWithValue("idc", client.id);
                    cmd.Parameters.AddWithValue("ide", evenimente[int.Parse((sender as Button).Tag.ToString())].id);
                    //verificare
                    if (cmd.ExecuteNonQuery() != 0)
                    {
                        MailMessage mail = new MailMessage();
                        mail.From = new MailAddress("igymromania@gmail.com");
                        mail.To.Add(client.email);
                        mail.Subject = "Rezervare facuta cu succes";
                        mail.Body = "Ati rezervat cu succes un loc la evenimentul: " + evenimente[int.Parse((sender as Button).Tag.ToString())].nume + '\n' + "Pretul este de: " + evenimente[int.Parse((sender as Button).Tag.ToString())].pret + " lei/luna." + '\n' + '\n' + '\n' + "IGym \nAdresa: Iaşi, Strada Petre Andrei 9, Iaşi 700496\nTelefon: 0771 518 956";

                        SmtpClient server = new SmtpClient("smtp.gmail.com");
                        server.Port = 587;
                        server.UseDefaultCredentials = false;
                        server.Credentials = new NetworkCredential("igymromania@gmail.com", "dzze yard bwmq qkax");
                        server.EnableSsl = true;

                        server.Send(mail);
                        MessageBox.Show("Loc la eveniment rezervat cu succes!", "Rezervare eveniment", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    else
                    {
                        MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
            else
            {
                MessageBox.Show("Aveti deja un loc rezervat pentru acest eveniment!", "Rezervare eveniment", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
        #endregion
        //---------------------------



        private void pbback1_Click(object sender, EventArgs e)
        {
            pnlevent.Visible = false;
            pnlmain.Visible = true;
            pnlab.Visible = false;
            pnlrez.Visible = false;
        }

        private void pbrez_Click(object sender, EventArgs e)
        {
            pnlrez.Visible = true;
            pnlevent.Visible = false;
            pnlmain.Visible = false;
            pnlab.Visible = false;

            dtev.Rows.Clear();
            try
            {
                //creare conexiune
                MySqlConnection connection = new MySqlConnection();
                connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                connection.Open();

                //creare comanda   
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;
                cmd.CommandText = @"Select *,evenimente.pret as pretev, evenimente.nume as numeevent from rezevenimente inner join clienti on rezevenimente.idc = clienti.idc inner join evenimente on rezevenimente.ide = evenimente.ide where rezevenimente.idc = @idc";

                cmd.Parameters.AddWithValue("idc", client.id);
                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                string[] s = new string[100];
                while (r.Read())
                {
                    s[0] = r["idre"].ToString();
                    s[1] = r["numeevent"].ToString();
                    s[2] = r["pretev"].ToString();
                    dtev.Rows.Add(s);
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            dtab.Rows.Clear();
            try
            {
                //creare conexiune
                MySqlConnection connection = new MySqlConnection();
                connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                connection.Open();

                //creare comanda   
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;
                cmd.CommandText = @"Select *,abonamente.pret as pretab, abonamente.nume as numeab from rezabonamente inner join clienti on rezabonamente.idc = clienti.idc inner join abonamente on rezabonamente.idab = abonamente.idab where rezabonamente.idc = @idc";

                cmd.Parameters.AddWithValue("idc", client.id);
                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                string[] s = new string[100];
                while (r.Read())
                {
                    s[0] = r["idra"].ToString();
                    s[1] = r["numeab"].ToString();
                    s[2] = r["pretab"].ToString();
                    dtab.Rows.Add(s);
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            pnlevent.Visible = false;
            pnlmain.Visible = true;
            pnlab.Visible = false;
            pnlrez.Visible = false;
        }

        private void pbback2_Click(object sender, EventArgs e)
        {
            pnlevent.Visible = false;
            pnlmain.Visible = true;
            pnlab.Visible = false;
            pnlrez.Visible = false;
        }
    }
}
