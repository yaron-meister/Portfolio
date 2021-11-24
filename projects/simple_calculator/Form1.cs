using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SimpleCalculator
{
    public partial class Form1 : Form
    {
        const Int16 MaxScreenLength = 10;
        string      _currentOper    = "+";
        decimal     _lValue         = 0.0m;
        bool        _isOperandWritten = false;

        public Form1()
        {
            InitializeComponent();
        }

        private void HandleOperator(string oper)
        {
            switch (oper)
            {
                case "+":
                case "-":
                case "*":
                case "/":
                    _lValue = Convert.ToDecimal(screen.Text);
                    _currentOper = oper;
                    _isOperandWritten = false;
                    break;
                case "=":
                    HandleResult();
                    break;
                default:
                    break;
            }
        }

        private void HandleOperand(string digit)
        {
            if (screen.Text.Length < MaxScreenLength && 
                ("." != digit || !screen.Text.Contains(".")))
            {
                if (!_isOperandWritten && "." != digit)
                {
                    screen.Text = digit;
                }
                else
                {
                    // Concatenating digit/point to the value
                    screen.Text += digit;
                }

                _isOperandWritten = true;
            }
        }

        private void HandleResult()
        {
            
            decimal rValue  = Convert.ToDecimal(screen.Text);
            decimal result  = 0.0m;
            bool    isError = false;

            switch (_currentOper)
            {
                case "+":
                    result = _lValue + rValue;
                    break;
                case "-":
                    result = _lValue - rValue;
                    break;
                case "*":
                    result = _lValue * rValue;
                    break;
                case "/":
                    try
                    {
                        result = _lValue / rValue;
                    }
                    catch (Exception ex) 
                    {
                        // Dividing in zero
                        isError = true;
                    }
                    break;
                default:
                    isError = true;
                    break;
            }

            if (!isError)
            {
                screen.Text = Convert.ToString(result);
                TrimScreenText();
                // Clear zeros from the end of the string
                screen.Text.TrimEnd('0'); 
            }
            else
            {
                screen.Text = "ERROR";
            }
            
            _isOperandWritten = false;
        }

        private void TrimScreenText()
        {
            int numOfCharsToRemove =
                screen.Text.Length - MaxScreenLength;

            if (numOfCharsToRemove > 0)
            {
                StringBuilder stringBuilder = 
                    new StringBuilder(screen.Text);
                stringBuilder.Remove(MaxScreenLength - 1, numOfCharsToRemove);
                screen.Text = stringBuilder.ToString();
            }
        }

        private void ResetCalculator()
        {
            _lValue = 0.0m;
            _currentOper = "+";
            _isOperandWritten = false;
            screen.Text = "0";
        }

        private void button0_Click(object sender, EventArgs e)
        {
            HandleOperand("0");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            HandleOperand("1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            HandleOperand("2");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            HandleOperand("3");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            HandleOperand("4");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            HandleOperand("5");
        }

        private void button6_Click(object sender, EventArgs e)
        {
            HandleOperand("6");
        }

        private void button7_Click(object sender, EventArgs e)
        {
            HandleOperand("7");
        }

        private void button8_Click(object sender, EventArgs e)
        {
            HandleOperand("8");
        }

        private void button9_Click(object sender, EventArgs e)
        {
            HandleOperand("9");
        }

        private void buttonPnt_Click(object sender, EventArgs e)
        {
            HandleOperand(".");
        }

        private void buttonMinus_Click(object sender, EventArgs e)
        {
            if ("0" != screen.Text)
            {
                screen.Text = Convert.ToString(-1 * Convert.ToDecimal(screen.Text));
            }
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            ResetCalculator();
        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            HandleOperator("+");
        }

        private void buttonSubtract_Click(object sender, EventArgs e)
        {
            HandleOperator("-");
        }

        private void buttonMultiple_Click(object sender, EventArgs e)
        {
            HandleOperator("*");
        }

        private void buttonDivide_Click(object sender, EventArgs e)
        {
            HandleOperator("/");
        }

        private void buttonEquals_Click(object sender, EventArgs e)
        {
            HandleOperator("=");
        }
    }
}
