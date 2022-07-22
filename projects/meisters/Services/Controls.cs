using Meisters.Models;
using Meisters.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Meisters.Services
{
    public class TableCheckBox : CheckBox
    {
        public ETableStatus Status
        {
            get => (ETableStatus)GetValue(StatusProperty);
            set => SetValue(StatusProperty, value);
        }
        public static readonly DependencyProperty StatusProperty =
            DependencyProperty.Register(nameof(Status), typeof(ETableStatus),
                                        typeof(TableCheckBox), new PropertyMetadata(ETableStatus.Clear));
    }

    public class EmployeeButton : Button
    {
        public bool IsSelected
        {
            get => (bool)GetValue(IsSelectedProperty);
            set => SetValue(IsSelectedProperty, value);
        }
        public static readonly DependencyProperty IsSelectedProperty =
            DependencyProperty.Register(nameof(IsSelected), typeof(bool),
                                        typeof(EmployeeButton), new PropertyMetadata(false));
    }
}
