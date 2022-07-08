using Meisters.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.ViewModels
{
    class FloorViewModel : ViewModelBase
    {
        // TODO::YARON - Get it from the model (it gets it through DB)
        public ObservableCollection<Employee> Employees { get; } = new ObservableCollection<Employee>
        {
            new Employee ("Yaron", true, 100),
            new Employee ("May", true, 101),
            new Employee ("Mika", false, 102),
            new Employee ("Dean", false, 103)
        };
    }
}
