using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace Gestiune_sala_crossfit
{
    public partial class frmAdmin : Form
    {
        public frmAdmin()
        {
            InitializeComponent();
        }

        private void frmAdmin_Load(object sender, EventArgs e)
        {
            evdate.Format = DateTimePickerFormat.Custom;
            evdate.CustomFormat = "dd/MM/yyyy HH:mm";
        }

        private void btnew_Click(object sender, EventArgs e)
        {
            string imagine="";
            if(ofd.FileName!="")
            {
                imagine = "Poze\\" + ofd.SafeFileName;
                string path = ofd.FileName;
                File.Copy(path, AppDomain.CurrentDomain.BaseDirectory + imagine);
            }
            else
            {

            }
            MessageBoxButtons buttons = MessageBoxButtons.YesNo;
            DialogResult result = MessageBox.Show("Sigur doriti sa adaugati un antrenor nou?", "Adaugare antrenor", buttons);
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
                    cmd.CommandText = @"INSERT INTO antrenori(nume,varsta,descriere,spec,cale) VALUES(@pnume,@pvarsta,@pdescriere,@pspec,@pcale);";

                    //stabilirea parametrilor 
                    cmd.Parameters.AddWithValue("pnume", tbnewnume.Text);
                    cmd.Parameters.AddWithValue("pvarsta", newdate.Value.Date);
                    cmd.Parameters.AddWithValue("pdescriere", tbnewdesc.Text);
                    cmd.Parameters.AddWithValue("pspec", tbnewspec.Text);
                    cmd.Parameters.AddWithValue("pcale", imagine);

                    //verificare
                    if (cmd.ExecuteNonQuery() != 0)
                    {
                        MessageBox.Show("Antrenor adaugat!", "Adaugare antrenor", MessageBoxButtons.OK, MessageBoxIcon.Information);
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

        private void btnant_Click(object sender, EventArgs e)
        {
            pnlant.Visible = true;
            pnlant.BringToFront();
        }

        private void btnevent_Click(object sender, EventArgs e)
        {
            pnlevent.Visible = true;
            pnlevent.BringToFront();
        }

        private void btnev_Click(object sender, EventArgs e)
        {
            string imagine = "";
            if (ofd.FileName != "")
            {
                imagine = "Poze\\" + ofd.SafeFileName;
                string path = ofd.FileName;
                File.Copy(path, AppDomain.CurrentDomain.BaseDirectory + imagine);
            }
            else
            {

            }
            MessageBoxButtons buttons = MessageBoxButtons.YesNo;
            DialogResult result = MessageBox.Show("Sigur doriti sa creati un eveniment nou?", "Adaugare eveniment", buttons);
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
                    cmd.CommandText = @"INSERT INTO evenimente(nume,descriere,data,cale,pret) VALUES(@pnume,@pdescriere,@pdata,@pcale,@ppret);";

                    //stabilirea parametrilor 
                    cmd.Parameters.AddWithValue("pnume", tbevnume.Text);
                    cmd.Parameters.AddWithValue("pdescriere", tbevdes.Text);
                    cmd.Parameters.AddWithValue("pdata", evdate.Value);
                    cmd.Parameters.AddWithValue("pcale", imagine);
                    cmd.Parameters.AddWithValue("ppret", tbevpret.Text);

                    //verificare
                    if (cmd.ExecuteNonQuery() != 0)
                    {
                        MessageBox.Show("Eveniment creat!", "Creare eveniment", MessageBoxButtons.OK, MessageBoxIcon.Information);
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

        private void btnpoza_Click(object sender, EventArgs e)
        {
            ofd.Title = "Alege o poza";
            ofd.Filter = "Image Files (*.jpg)|*.jpg|All Files(*.*)|*";
            
            if(ofd.ShowDialog()==DialogResult.OK)
            {
                pbpoza.Image = Image.FromFile(ofd.FileName);
                pbpoza.SizeMode = PictureBoxSizeMode.StretchImage;
            }
        }

        private void ofd_FileOk(object sender, CancelEventArgs e)
        {
           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ofd.Title = "Alege o poza";
            ofd.Filter = "Image Files (*.jpg)|*.jpg|All Files(*.*)|*";

            if (ofd.ShowDialog() == DialogResult.OK)
            {
                pbev.Image = Image.FromFile(ofd.FileName);
                pbev.SizeMode = PictureBoxSizeMode.StretchImage;
            }
        }

        private void btnab_Click(object sender, EventArgs e)
        {
            pnlab.Visible = true;
            pnlab.BringToFront();
        }

        private void btnnewab_Click(object sender, EventArgs e)
        {
            MessageBoxButtons buttons = MessageBoxButtons.YesNo;
            DialogResult result = MessageBox.Show("Sigur doriti sa creati un abonament nou?", "Adaugare abonament", buttons);
            if (result == DialogResult.Yes)
            {
                try
                {
                    string tip = "";
                    if (rbpersonal.Checked == true)
                    {
                        tip = "personal";
                    }
                    if (rbgrup.Checked == true)
                    {
                        tip = "grup";
                    }

                    //creare conexiune
                    MySqlConnection connection = new MySqlConnection();
                    connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                    connection.Open();

                    //creare comanda   
                    MySqlCommand cmd = new MySqlCommand();
                    cmd.Connection = connection;
                    cmd.CommandText = @"INSERT INTO abonamente(nume,tip,descriere,pret) VALUES(@pnume,@ptip,@pdescriere,@ppret);";

                    //stabilirea parametrilor 
                    cmd.Parameters.AddWithValue("pnume", tbnumeab.Text);
                    cmd.Parameters.AddWithValue("pdescriere", tbdescab.Text);
                    cmd.Parameters.AddWithValue("ppret", tbpretab.Text);
                    cmd.Parameters.AddWithValue("ptip", tip);

                    //verificare
                    if (cmd.ExecuteNonQuery() != 0)
                    {
                        MessageBox.Show("Abonament creat!", "Creare abonament", MessageBoxButtons.OK, MessageBoxIcon.Information);
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

        private void tbpretab_TextChanged(object sender, EventArgs e)
        {

        }

        private void evdate_ValueChanged(object sender, EventArgs e)
        {

        }
        //----------baze de date
        #region baze de date
        private void btnstergere_Click(object sender, EventArgs e)
        {
            pnlstergere.Visible = true;
            pnlstergere.BringToFront();
            dtant.Rows.Clear();
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

                string[] s = new string[100];
                while (r.Read())
                {
                    s[0] = r["ida"].ToString();
                    s[1] = r["nume"].ToString();
                    s[2] = r["spec"].ToString();
                    s[3] = r["varsta"].ToString();
                    dtant.Rows.Add(s);
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
                cmd.CommandText = @"Select * from abonamente";

                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                string[] s = new string[100];
                while (r.Read())
                {
                    s[0] = r["idab"].ToString();
                    s[1] = r["nume"].ToString();
                    s[2] = r["tip"].ToString();
                    s[3] = r["pret"].ToString();
                    dtab.Rows.Add(s);
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            dtevent.Rows.Clear();
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

                string[] s = new string[100];
                while (r.Read())
                {
                    s[0] = r["ide"].ToString();
                    s[1] = r["nume"].ToString();
                    s[2] = r["data"].ToString();
                    s[3] = r["pret"].ToString();
                    dtevent.Rows.Add(s);
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
        #endregion
        //--------------rezervari
        #region rezervari
        private void btnrez_Click(object sender, EventArgs e)
        {
            dtrezev.Rows.Clear();
            try
            {
                //creare conexiune
                MySqlConnection connection = new MySqlConnection();
                connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                connection.Open();

                //creare comanda   
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;
                cmd.CommandText = @"Select *,clienti.nume as numeclient, evenimente.nume as numeevent from rezevenimente inner join clienti on rezevenimente.idc = clienti.idc inner join evenimente on rezevenimente.ide = evenimente.ide";

                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                string[] s = new string[100];
                while (r.Read())
                {
                    s[0] = r["idre"].ToString();
                    s[1] = r["numeclient"].ToString();
                    s[2] = r["numeevent"].ToString();
                    dtrezev.Rows.Add(s);
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            dtrezab.Rows.Clear();
            try
            {
                //creare conexiune
                MySqlConnection connection = new MySqlConnection();
                connection.ConnectionString = @"Server=localhost; DATABASE=IGym; UID=root; PASSWORD=; allow User Variables=True";
                connection.Open();

                //creare comanda   
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;
                cmd.CommandText = @"Select *,clienti.nume as numeclient, abonamente.nume as numeab from rezabonamente inner join clienti on rezabonamente.idc = clienti.idc inner join abonamente on rezabonamente.idab = abonamente.idab";

                //reader
                MySqlDataReader r = cmd.ExecuteReader();

                string[] st = new string[100];
                while (r.Read())
                {
                    st[0] = r["idra"].ToString();
                    st[1] = r["numeclient"].ToString();
                    st[2] = r["numeab"].ToString();
                    dtrezab.Rows.Add(st);
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            pnlrez.Visible = true;
            pnlrez.BringToFront();
        }
        #endregion

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void btndel1_Click(object sender, EventArgs e)
        {
            if(dtant.SelectedRows.Count > 0 )
            {
                MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                DialogResult result = MessageBox.Show("Sigur doriti sa stergeti acest antrenor?", "Stergere antrenor", buttons);
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
                        cmd.CommandText = @"DELETE from antrenori  WHERE ida = @id";

                        cmd.Parameters.AddWithValue("id", int.Parse(dtant.SelectedRows[0].Cells[0].Value.ToString()));

                        if (cmd.ExecuteNonQuery() != 0)
                        {
                            MessageBox.Show("Sters!", "Stergere antrenor", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }

                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    dtant.Rows.RemoveAt(dtant.SelectedRows[0].Index);
                }
            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            pnltabant.Visible = true;
            pnltabevent.Visible = false;
            pnltabab.Visible = false;

        }

        private void button3_Click(object sender, EventArgs e)
        {
            pnltabant.Visible = false;
            pnltabevent.Visible = true;
            pnltabab.Visible = false;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            pnltabant.Visible = false;
            pnltabevent.Visible = false;
            pnltabab.Visible = true;
        }

        private void btndel2_Click(object sender, EventArgs e)
        {
            if (dtevent.SelectedRows.Count > 0)
            {
                MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                DialogResult result = MessageBox.Show("Sigur doriti sa stergeti acest eveniment?", "Stergere eveniment", buttons);
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
                        cmd.CommandText = @"DELETE from evenimente  WHERE ide = @ide";

                        cmd.Parameters.AddWithValue("ide", int.Parse(dtevent.SelectedRows[0].Cells[0].Value.ToString()));

                        if (cmd.ExecuteNonQuery() != 0)
                        {
                            MessageBox.Show("Sters!", "Stergere eveniment", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }

                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    dtevent.Rows.RemoveAt(dtab.SelectedRows[0].Index);
                }
            }
        }

        private void btndel3_Click(object sender, EventArgs e)
        {
            if (dtab.SelectedRows.Count > 0)
            {
                MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                DialogResult result = MessageBox.Show("Sigur doriti sa stergeti acest abonament?", "Stergere abonament", buttons);
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
                        cmd.CommandText = @"DELETE from abonamente  WHERE idab = @idab";

                        cmd.Parameters.AddWithValue("idab", int.Parse(dtab.SelectedRows[0].Cells[0].Value.ToString()));

                        if (cmd.ExecuteNonQuery() != 0)
                        {
                            MessageBox.Show("Sters!", "Stergere abonament", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }

                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    dtab.Rows.RemoveAt(dtab.SelectedRows[0].Index);
                }
                
            }
        }

        private void btn1_Click(object sender, EventArgs e)
        {
            if (dtrezev.SelectedRows.Count > 0)
            {
                MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                DialogResult result = MessageBox.Show("Sigur doriti sa stergeti aceasta rezervare?", "Stergere rezervare", buttons);
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
                        cmd.CommandText = @"DELETE from rezevenimente  WHERE idre = @idre";

                        cmd.Parameters.AddWithValue("idre", int.Parse(dtrezev.SelectedRows[0].Cells[0].Value.ToString()));

                        if (cmd.ExecuteNonQuery() != 0)
                        {
                            MessageBox.Show("Sters!", "Stergere rezervare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }

                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    dtrezev.Rows.RemoveAt(dtrezev.SelectedRows[0].Index);
                }

            }
        }

        private void btn2_Click(object sender, EventArgs e)
        {
            if (dtrezab.SelectedRows.Count > 0)
            {
                MessageBoxButtons buttons = MessageBoxButtons.YesNo;
                DialogResult result = MessageBox.Show("Sigur doriti sa stergeti aceasta rezervare?", "Stergere rezervare", buttons);
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
                        cmd.CommandText = @"DELETE from rezabonamente  WHERE idra = @idra";

                        cmd.Parameters.AddWithValue("idra", int.Parse(dtrezab.SelectedRows[0].Cells[0].Value.ToString()));

                        if (cmd.ExecuteNonQuery() != 0)
                        {
                            MessageBox.Show("Sters!", "Stergere rezervare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }

                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show("A aparut o eroare, va rugam sa contactati un administrator!", "Eroare", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    dtrezab.Rows.RemoveAt(dtrezab.SelectedRows[0].Index);
                }

            }
        }
    }
}
