using GalaSoft.MvvmLight.Command;
using Meisters.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Meisters.ViewModels
{
    class FloorViewModel : ViewModelBase
    {
        readonly Employee GENERAL_EMPLOYEE = new Employee("General", false, 100);

        public FloorViewModel()
        {
            Employees.Add(GENERAL_EMPLOYEE);
            SelectedActiveEmployee = GENERAL_EMPLOYEE;
        }

        // TODO::YARON - Get it from the model (it gets it through DB)
        public ObservableCollection<Employee> Employees { get; } = new ObservableCollection<Employee>
        {
            new Employee ("May", true, 101),
            new Employee ("Mika", false, 102),
            new Employee ("Dean", false, 103),
            new Employee ("Yaron", true, 104),
        };

        public Employee SelectedActiveEmployee { get; set; }


        #region Commands

        public ICommand SelectActiveEmployee => new RelayCommand<Employee>((employee) =>
        {
            if (employee?.Uid != SelectedActiveEmployee.Uid)
            {
                SelectedActiveEmployee.IsSelected = false;
                employee.IsSelected = true;
                SelectedActiveEmployee = employee;
            }
        });

        #endregion Commands
    }
}
