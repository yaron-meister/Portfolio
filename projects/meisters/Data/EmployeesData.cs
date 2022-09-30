using Meisters.Models;
using Meisters.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Data
{
    public class EmployeesData : Observable
    {
        private Employee _selectedActiveEmployee;
        private ObservableCollection<Employee> _activeEmployees = new ObservableCollection<Employee>();
        private ObservableCollection<Employee> _inactiveEmployees = new ObservableCollection<Employee>()
        {
            // TODO::YARON - Get it from the model (it gets it through DB)
            new Employee ("May", true, 101),
            new Employee ("Mika", false, 102),
            new Employee ("Dean", false, 103),
            new Employee ("Yaron", true, 104),
        };

        public Employee GeneralEmployee { get; } = new Employee("General", false, 100);

        public Employee SelectedEmployee
        {
            get => _selectedActiveEmployee;
            set
            {
                _selectedActiveEmployee = value;
                OnPropertyChanged();
            }
        }

        public ObservableCollection<Employee> ActiveEmployees
        {
            get => _activeEmployees;
            set
            {
                _activeEmployees = value;
                OnPropertyChanged();
            }
        }

        public ObservableCollection<Employee> InactiveEmployees
        {
            get => _inactiveEmployees;
            set
            {
                _inactiveEmployees = value;
                OnPropertyChanged();
            }
        }
    }
}
