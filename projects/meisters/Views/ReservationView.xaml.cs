using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
    /// Interaction logic for ReservationView.xaml
    /// </summary>
    public partial class ReservationView : UserControl
    {
        public ReservationView()
        {
            InitializeComponent();
        }

        private void OnTabSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (sender is ReservationTabControl tabControl && tabControl.SelectedItem is ReservationTabItem tabItem)
            {
                tabControl.Theme = tabItem.Theme;
            }
        }
    }

    public class ReservationTabControl : TabControl
    {
        private static readonly SolidColorBrush WHITE_BRUSH =
            new SolidColorBrush(Color.FromRgb(255, 255, 255));

        public Brush Theme
        {
            get => (Brush)GetValue(ThemeProperty);
            set => SetValue(ThemeProperty, value);
        }
        public static readonly DependencyProperty ThemeProperty =
            DependencyProperty.Register(nameof(Theme), typeof(Brush),
                                        typeof(ReservationTabControl), new PropertyMetadata(WHITE_BRUSH));
    }

    public class ReservationTabItem : TabItem
    {
        private static readonly SolidColorBrush WHITE_BRUSH =
            new SolidColorBrush(Color.FromRgb(255, 255, 255));

        public Brush Theme
        {
            get => (Brush)GetValue(ThemeProperty);
            set => SetValue(ThemeProperty, value);
        }
        public static readonly DependencyProperty ThemeProperty =
            DependencyProperty.Register(nameof(Theme), typeof(Brush),
                                        typeof(ReservationTabItem), new PropertyMetadata(WHITE_BRUSH));
    }
}
