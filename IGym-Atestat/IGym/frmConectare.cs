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
    public partial class frmConectare : Form
    {
        public frmConectare()
        {
            InitializeComponent();
        }
        public static frmClient clientul;
        public static frmAdmin admin;
        private void frmConectare_FormClosed(object sender, FormClosedEventArgs e)
        {
            frmMain.conect = null;
        }
        private void lblaici_Click(object sender, EventArgs e)
        {
            pnlnew.Visible = true;
            pnllogin.Visible = false;
        }
        private void btn1_Click(object sender, EventArgs e)
        {
            pnlselect.Visible = false;
            pnllogin.Visible = true;
            pnlnew.Visible = false;
        }

        private void btn2_Click(object sender, EventArgs e)
        {
            pnlselect.Visible = false;
            pnllogin.Visible = false;
            pnlnew.Visible = true;
        }

        //---------INREGISTRARE--------
        #region inregistrare
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
        private void btnnew_Click(object sender, EventArgs e)
        {
            int ok = 0;
            if (tbnewnume.ForeColor == Color.Black)
            {
                ok++;
                alert1.Visible = false;
            }
            else
            { 
                alert1.Visible = true;
            }
            if (tbnewparola.Text == tbcheckparola.Text)
            {
                ok++;
                alert3.Visible = false;
            }
            else
            {
                alert3.Visible = true;
            }
            if (tbnewtel.Text.Length == 10)
            {
                ok++;
                alert4.Visible = false;
            }
            else
            {
                alert4.Visible = true;
            }
            if (IsValidAddress(tbnewemail.Text) == true)
            {
                ok++;
                alert2.Visible = false;
            }
            else
            {
                alert2.Visible = true;
            }
            if (ok == 4)
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
                    cmd.CommandText = @"Select * from clienti where email = @email";

                    cmd.Parameters.AddWithValue("email",tbnewemail.Text);
                    //reader
                    MySqlDataReader r = cmd.ExecuteReader();

                    if(r.Read())
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
                        cmd.CommandText = @"INSERT INTO clienti(nume,datan,telefon,email,parola) VALUES(@pnume,@pdatan,@ptelefon,@pemail,@pparola);";

                        //stabilirea parametrilor 
                        cmd.Parameters.AddWithValue("pnume", tbnewnume.Text);
                        cmd.Parameters.AddWithValue("pdatan", newdate.Value.Date);
                        cmd.Parameters.AddWithValue("ptelefon", tbnewtel.Text);
                        cmd.Parameters.AddWithValue("pemail", tbnewemail.Text);
                        cmd.Parameters.AddWithValue("pparola", tbnewparola.Text);

                        //verificare
                        if (cmd.ExecuteNonQuery() != 0)
                        {
                            cmd.CommandText = "select @@Identity";
                            ulong id = (ulong)cmd.ExecuteScalar();
                            client.id = (int)id;
                            client.nume = tbnewnume.Text;
                            client.parola = tbnewparola.Text;
                            client.email = tbnewemail.Text;
                            client.tel = tbnewtel.Text;
                            client.data = newdate.Value.Date;
                            clientul = new frmClient();
                            clientul.Show();
                            connection.Close();
                            this.Close();
                            MessageBox.Show("Cont creat cu succes!", "Cont creat", MessageBoxButtons.OK, MessageBoxIcon.Information);
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
                    MessageBox.Show("Adresa de email deja folosita!", "Baze de date", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
        }
        #endregion
        //-----------------------DESIGN CREARE CONT---------
        #region design
        private void tbnewnume_KeyUp(object sender, KeyEventArgs e)
        {
            if ((e.KeyCode == Keys.Enter) || (e.KeyCode == Keys.Return))
            {
                tbnewemail.Focus();
            }
        }

        private void tbnewemail_KeyUp(object sender, KeyEventArgs e)
        {
            if ((e.KeyCode == Keys.Enter) || (e.KeyCode == Keys.Return))
            {
                tbnewparola.Focus();
            }
        }

        private void tbnewparola_KeyUp(object sender, KeyEventArgs e)
        {
            if ((e.KeyCode == Keys.Enter) || (e.KeyCode == Keys.Return))
            {
                tbcheckparola.Focus();
            }
        }

        private void tbcheckparola_KeyUp(object sender, KeyEventArgs e)
        {
            if ((e.KeyCode == Keys.Enter) || (e.KeyCode == Keys.Return))
            {
                newdate.Focus();
            }
        }

        private void newdate_KeyUp(object sender, KeyEventArgs e)
        {
            if ((e.KeyCode == Keys.Enter) || (e.KeyCode == Keys.Return))
            {
                tbnewtel.Focus();
            }
        }

        private void tb_Enter(object sender, EventArgs e)
        {
            TextBox tbox = sender as TextBox;

            if (tbox.ForeColor == Color.LightSteelBlue)
            {
                tbox.Text = "";
                tbox.ForeColor = Color.Black;
            }
        }
        private void tbpass_Enter(object sender, EventArgs e)
        {
            TextBox tbox = sender as TextBox;

            if (tbox.ForeColor == Color.LightSteelBlue)
            {
                tbox.Text = "";
                tbox.ForeColor = Color.Black;
                tbox.PasswordChar = '●';
            }
        }
        private void tbnewnume_Leave(object sender, EventArgs e)
        {
            if (tbnewnume.Text == "") 
            {
                tbnewnume.ForeColor = Color.LightSteelBlue;
                tbnewnume.Text = "Nume complet";
            }
        }

        private void tbnewemail_Leave(object sender, EventArgs e)
        {
            if (tbnewemail.Text == "")
            {
                tbnewemail.ForeColor = Color.LightSteelBlue;
                tbnewemail.Text = "Email";
            }
        }

        private void tbnewparola_Leave(object sender, EventArgs e)
        {
            if (tbnewparola.Text == "")
            {
                tbnewparola.PasswordChar = '\0';
                tbnewparola.ForeColor = Color.LightSteelBlue;
                tbnewparola.Text = "Parola";
            }
        }

        private void tbcheckparola_Leave(object sender, EventArgs e)
        {
            if (tbcheckparola.Text == "")
            {
                tbcheckparola.PasswordChar = '\0';
                tbcheckparola.ForeColor = Color.LightSteelBlue;
                tbcheckparola.Text = "Confirmare parola";
            }
        }

        private void tbnewtel_Leave(object sender, EventArgs e)
        {
            if (tbnewtel.Text == "")
            {
                tbnewtel.ForeColor = Color.LightSteelBlue;
                tbnewtel.Text = "Telefon";
            }
        }

        private void alert_MouseHover(object sender, EventArgs e)
        {
            PictureBox alert = sender as PictureBox;
            ToolTip tt = new ToolTip();
            tt.SetToolTip(alert, "Camp invalid!");
        }

        private void lblback_MouseHover(object sender, EventArgs e)
        {
            lblback.ForeColor = Color.RoyalBlue;
            lblback.Font = new Font("Microsoft Sans Serif",10,FontStyle.Underline);
        }

        private void lblback_MouseLeave(object sender, EventArgs e)
        {
            lblback.ForeColor = Color.Black;
            lblback.Font = new Font("Microsoft Sans Serif", 10, FontStyle.Regular);
        }

        private void lblback_Click(object sender, EventArgs e)
        {
            pnlnew.Visible = false;
            pnllogin.Visible = true;
        }

        private void tbnewtel_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }
        }
        #endregion
        //===============LOGIN==========
        #region login
        private void btnlogin_Click(object sender, EventArgs e)
        {
            if (tblogpass.Text == "admin" && tblogemail.Text == "igymromania@gmail.com")
            {
                admin = new frmAdmin();
                admin.Show();
                this.Close();
            }
            else
            {
                if (tblogemail.TextLength > 0 && tblogpass.TextLength > 0)
                {
                    try
                    {
                        MySqlConnection connection = new MySqlConnection();
                        connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";

                        connection.Open();

                        MySqlCommand cmd = new MySqlCommand();
                        cmd.Connection = connection;
                        cmd.CommandText = "SELECT * FROM clienti WHERE email = @pemail AND  parola = @pparola";
                        cmd.Parameters.AddWithValue("pemail", tblogemail.Text);
                        cmd.Parameters.AddWithValue("pparola", tblogpass.Text);

                        MySqlDataReader r = cmd.ExecuteReader();


                        if (r.Read() && r["parola"].ToString() == tblogpass.Text)
                        {
                            client.id = int.Parse(r["idc"].ToString());
                            client.nume = r["nume"].ToString();
                            client.email = r["email"].ToString();
                            client.parola = r["parola"].ToString();
                            client.tel = r["telefon"].ToString();
                            clientul = new frmClient();
                            clientul.Show();
                            r.Close();
                            connection.Close();
                            this.Close();
                        }
                        else
                        {
                            MessageBox.Show("Email sau parola invalida!");
                        }
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }

                }
                else
                {
                    MessageBox.Show("Email sau parola invalida!");
                }
            }
        }
        #endregion

        private void lblaici_MouseHover(object sender, EventArgs e)
        {
                lblaici.ForeColor = Color.RoyalBlue;
                lblaici.Font = new Font("Microsoft Sans Serif", 10, FontStyle.Underline);
        }

        private void lblaici_MouseLeave(object sender, EventArgs e)
        {
            lblaici.ForeColor = Color.Black;
            lblaici.Font = new Font("Microsoft Sans Serif", 10, FontStyle.Regular);
        }
    }

}
