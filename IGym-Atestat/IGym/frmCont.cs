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

namespace Gestiune_sala_crossfit
{
    public partial class frmCont : Form
    {
        public frmCont()
        {
            InitializeComponent();
        }

        private void pbback1_Click(object sender, EventArgs e)
        {

        }

        private void frmCont_Load(object sender, EventArgs e)
        {
            tbnume.Text = client.nume;
            tbtel.Text = client.tel;
            lblemail.Text = client.email;
        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void btnlogin_Click(object sender, EventArgs e)
        {
            MessageBoxButtons buttons = MessageBoxButtons.YesNo;
            DialogResult result = MessageBox.Show("Sigur doriti sa modificati datele?", "Modificare date", buttons);
            if (result == DialogResult.Yes)
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
                    cmd.CommandText = @"UPDATE clienti SET `nume`=@nume,`telefon`=@telefon where idc=@idc";

                    cmd.Parameters.AddWithValue("nume", tbnume.Text);
                    cmd.Parameters.AddWithValue("telefon", tbtel.Text);
                    cmd.Parameters.AddWithValue("idc", client.id);


                    if (cmd.ExecuteNonQuery() != 0)
                    {
                        MessageBox.Show("Date modificate!", "Date modificate", MessageBoxButtons.OK, MessageBoxIcon.Information);
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
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (tbnew.Text==tbnew2.Text && tbnew.Text!="")
            { 
                MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                DialogResult result = MessageBox.Show("Sigur doriti sa modificati parola?", "Modificare parola", buttons);
                if (result == DialogResult.Yes)
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
                        cmd.CommandText = @"UPDATE clienti SET `parola`=@parola where idc=@idc";

                        cmd.Parameters.AddWithValue("parola", tbnew.Text);
                        cmd.Parameters.AddWithValue("idc", client.id);


                        if (cmd.ExecuteNonQuery() != 0)
                        {
                            MessageBox.Show("Parola modificata!", "Parola modificata", MessageBoxButtons.OK, MessageBoxIcon.Information);
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
            }
            else
            {
                MessageBox.Show("Parolele nu coincid", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
    }
}
