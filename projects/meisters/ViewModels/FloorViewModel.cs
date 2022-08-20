using GalaSoft.MvvmLight.Command;
using Meisters.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Windows.Threading;

namespace Meisters.ViewModels
{
    class FloorViewModel : ViewModelBase
    {
        private readonly int ONE_MINUTE = 1;

        private Employee _selectedActiveEmployee;
        private string _searchText = string.Empty;
        private bool _isActivatingEmp = false;
        private DispatcherTimer _dispatcherTimer = new DispatcherTimer();
        private Table[] _tables = new Table[24];
        private ObservableCollection<Employee> _activeEmployees = new ObservableCollection<Employee>();
        private IEnumerable<Employee> _filteredInactiveEmployees = new ObservableCollection<Employee>();
        private ObservableCollection<Employee> _inactiveEmployees = new ObservableCollection<Employee>()
        {
            // TODO::YARON - Get it from the model (it gets it through DB)
            new Employee ("May", true, 101),
            new Employee ("Mika", false, 102),
            new Employee ("Dean", false, 103),
            new Employee ("Yaron", true, 104),
        };

        public FloorViewModel()
        {
            ActiveEmployees.Add(GeneralEmployee);
            SelectActiveEmployee(GeneralEmployee);

            for (int idx = 0; idx < Tables.Length; ++idx)
            {
                Tables[idx] = new Table(idx);
            }

            // This DispatcherTimer is for updating the Tables stopwatches in the UI
            _dispatcherTimer.Tick += (object sender, EventArgs e) =>
            {
                OnPropertyChanged(nameof(Tables));
            };
            _dispatcherTimer.Interval = new TimeSpan(0, ONE_MINUTE, 0);
            _dispatcherTimer.Start();
        }


        public Employee GeneralEmployee { get; } = new Employee("General", false, 100);

        public Employee SelectedActiveEmployee
        {
            get => _selectedActiveEmployee;
            set
            {
                _selectedActiveEmployee = value;
                OnPropertyChanged();
            }
        }

        public string SearchText
        {
            get => _searchText;
            set
            {
                _searchText = value;
                OnPropertyChanged();
                FilterInactiveEmployees();
            }
        }

        public bool IsActivatingEmp
        {
            get => _isActivatingEmp;
            set
            {
                _isActivatingEmp = value;
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

        public IEnumerable<Employee> FilteredInactiveEmployees
        {
            get => _filteredInactiveEmployees;
            set
            {
                _filteredInactiveEmployees = value;
                OnPropertyChanged();
            }
        }

        public Table[] Tables
        {
            get => _tables;
            set
            {
                _tables = value;
                OnPropertyChanged();
            }
        }


        #region Commands

        public ICommand SelectActiveEmployeeCommand => new RelayCommand<Employee>((employee) =>
        {
            if (employee?.Uid != SelectedActiveEmployee?.Uid)
            {
                if (SelectedActiveEmployee != null)
                {
                    SelectedActiveEmployee.IsSelected = false;
                }
                SelectActiveEmployee(employee);
            }
        });

        public ICommand ActivateEmployeeCommand => new RelayCommand(() =>
        {
            FilteredInactiveEmployees = InactiveEmployees;
            IsActivatingEmp = true;
            SelectedActiveEmployee = null;
        });

        public ICommand DiscardEmployeeCommand => new RelayCommand<Employee>((employee) =>
        {
            if (employee != null && employee != GeneralEmployee)
            {
                InactiveEmployees.Add(employee);
                ActiveEmployees.Remove(employee);
                SelectedActiveEmployee = GeneralEmployee;
            }
        });

        public ICommand ActivateSelectedEmpCommand => new RelayCommand<Employee>((employee) =>
        {
            if (employee != null && employee != GeneralEmployee)
            {
                ActiveEmployees.Add(employee);
                InactiveEmployees.Remove(employee);
                CloseEmpActivision();
            }
        });

        public ICommand CancelEmpActivisionCommand => new RelayCommand(() =>
        {
            CloseEmpActivision();
        });

        public ICommand StepIntoTableCommand => new RelayCommand<string>((idStr) =>
        {
            if (int.TryParse(idStr, out int id) && id >= 0 && id < Tables.Length)
            {
                // TODO::YARON - Update this logic
                if (Tables[id].Status == ETableStatus.Clear)
                {
                    Tables[id].Status = ETableStatus.NoOrder;
                    Tables[id].TotalStopwatch.Start();
                    Tables[id].StatusStopwatch.Start();
                    OnPropertyChanged(nameof(Tables));
                }
            }
        });

        #endregion Commands

        private void SelectActiveEmployee(Employee employee)
        {
            SelectedActiveEmployee = employee;
            SelectedActiveEmployee.IsSelected = true;
        }

        private void FilterInactiveEmployees()
        {
            if (!string.IsNullOrEmpty(SearchText))
            {
                FilteredInactiveEmployees = InactiveEmployees.Where(employee =>
                                                employee.Name.ToLower().Contains(SearchText.ToLower()));
            }
            else
            {
                FilteredInactiveEmployees = InactiveEmployees;
            }
        }

        private void CloseEmpActivision()
        {
            IsActivatingEmp = false;
            SelectedActiveEmployee = GeneralEmployee;
        }
    }
}
