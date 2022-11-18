﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Meisters.Views
{
    /// <summary>
    /// Interaction logic for DinersNumView.xaml
    /// </summary>
    public partial class DinersNumView : UserControl
    {
        public DinersNumView()
        {
            InitializeComponent();
        }

        private void OnPreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[^0-9]+");
            e.Handled = regex.IsMatch(e.Text);
        }

        private void OnVisibilityChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            dinersNumText.Text = string.Empty;
            if (dinersNumText.IsVisible)
            {
                FocusManager.SetFocusedElement(FocusManager.GetFocusScope(sender as DependencyObject), dinersNumText);
            }
        }
    }
}
