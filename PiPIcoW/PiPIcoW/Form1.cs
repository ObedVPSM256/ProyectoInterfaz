using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PiPIcoW
{
    public partial class Form1 : Form
    {
        SerialPort port;
        public Form1()
        {
            InitializeComponent();
            RefreshPortList();
        }

        private void RefreshPortList()
        {
            // Limpia la lista de puertos
            comboBox1.Items.Clear();

            // Obtiene la lista de puertos disponibles
            string[] ports = SerialPort.GetPortNames();

            // Agrega los puertos a la lista
            foreach (string portName in ports)
            {
                try
                {
                    using (SerialPort testPort = new SerialPort(portName))
                    {
                        testPort.Open();
                        comboBox1.Items.Add(portName);
                        testPort.Close();
                    }
                }
                catch (UnauthorizedAccessException)
                {
                    // El puerto está en uso, se ignora
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error al comprobar el puerto: " + ex.Message);
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (string.IsNullOrEmpty(comboBox1.Text))
                {
                    MessageBox.Show("Seleccione un puerto antes de conectar.");
                    return;
                }

                if (port != null && port.IsOpen)
                {
                    port.Close();
                }

                port = new SerialPort
                {
                    PortName = comboBox1.Text,
                    BaudRate = 115200,
                    DtrEnable = true
                };

                port.DataReceived += Port_DataReceived;
                port.Open();

                if (port.IsOpen)
                {
                    MessageBox.Show("Conexión establecida correctamente 🙂");
                    comboBox1.Enabled = false;
                    button1.Enabled = false;
                    button1.Text = "Conectado";
                }
                else
                {
                    MessageBox.Show("No se pudo abrir el puerto. Verifica la conexión y el puerto seleccionado.");
                }
            }
            catch (UnauthorizedAccessException)
            {
                MessageBox.Show("Acceso denegado al puerto seleccionado.");
            }
            catch (IOException)
            {
                MessageBox.Show("Error de E/S al intentar conectar con el puerto.");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error al intentar conectar: " + ex.Message);
            }
        }

        private void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            // Aquí puedes manejar los datos recibidos del puerto serie
            string data = port.ReadExisting();
            Invoke(new Action(() => textBox1.AppendText(data)));
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                if (port != null && port.IsOpen)
                {
                    string message = textBox1.Text;
                    port.WriteLine(message);
                    label1.Text = $"Mensaje enviado: {message}";
                    MessageBox.Show("Mensaje enviado correctamente");
                }
                else
                {
                    MessageBox.Show("El puerto no está abierto. Abre la conexión antes de enviar datos.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error al enviar datos: " + ex.Message);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
        }
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            base.OnFormClosing(e);
            if (port != null && port.IsOpen)
            {
                port.Close();
            }
        }
    }
}
